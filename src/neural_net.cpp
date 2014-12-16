
#include <stdlib.h>

#include <NeuRL/neural_net.h>
#include <NeuRL/activation_functions.h>

namespace NeuRL {

NeuralNet::NeuralNet(const std::vector<int> &layers, double epsilon, double learningRate) : epsilon_(epsilon), learningRate_(learningRate), regularization_(0.1) {

  int count = 0;
  for (int i = 0; i < layers.size(); i++) {
    //Copy over the layers from the input
    layers_.push_back(layers[i]);

    if (i == (layers.size() -1)) {
      break;
    }

    //Initialize the weights randomly
    for (int j = 0; j < layers[i]*layers[i+1]; j++) {
      theta_[count++] = ( (double)rand() / RAND_MAX) * 2.0 * epsilon_ - epsilon_; 
    }
  }

}

void NeuralNet::propagate(const std::vector<double> &x, std::vector<double> &a) const {

  int length = layers_.size();

  //Declare a matrix for each layer of weights in the network
  std::vector<Eigen::MatrixXd> theta_mat(length-1);

  //Populate the matrices from the weights
  int flag = 0;
  for (int i = 0; i < length-1; i++) {
    int size = layers_[i+1] * (layers_[i]+1);
    std::vector<double> vec(&theta_[flag], &theta_[flag+size]);
    theta_mat[i] = Eigen::Map<Eigen::MatrixXd>(vec.data(), layers_[i+1], layers_[i]);
    flag = flag + size;
  }

  //Declare the layers as a giant list
  std::vector<Eigen::VectorXd> layerX(length);

  //Initialize the first layer with a bias node added to the input
  std::vector<double> vec0 = x;
  vec0.insert(vec0.begin(), 1);
  layerX[0] = Eigen::Map<Eigen::VectorXd>(vec0.data(), vec0.size());

  //Loop through and propagate through each layer
  for (int i = 1; i < length; i++) {
    //Convert to STL vector type
    Eigen::VectorXd Z = theta_mat[i-1]*layerX[i-1];
    std::vector<double> z(Z.size());
    for (int j = 0; j < z.size(); j++) {
      z[j] = Z[j];
    }

    //Compute the sigmoid
    std::vector<double> r;
    sigmoid(z, r);

    //Add bias node if not at the end
    if (i < (length-1)) {
      r.insert(r.begin(), 1);
    }

    layerX[i] = Eigen::Map<Eigen::VectorXd>(r.data(), r.size());

  }

  //Store off the layers
  activation_ = layerX;

  //Copy the result to the output
  for (int i = 0; i < layerX[length-1].size(); i++) {
    a[i] = layerX[length-1][i];
  }
}

void NeuralNet::update(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &a) {

  int length = layers_.size();

  //Declare a matrix for each layer of weights in the network
  std::vector<Eigen::MatrixXd> theta_mat(length-1);

  //Populate the matrices from the weights
  int flag = 0;
  for (int i = 0; i < length-1; i++) {
    int size = layers_[i+1] * (layers_[i]+1);
    std::vector<double> vec(&theta_[flag], &theta_[flag+size]);
    theta_mat[i] = Eigen::Map<Eigen::MatrixXd>(vec.data(), layers_[i+1], layers_[i]);
    flag = flag + size;
  }

  //Declare error structure
  std::vector<Eigen::VectorXd> error(length);

  //Make a copy of the inputs so the arguments remain const
  std::vector<double> sy = y;
  std::vector<double> sa = a;

  //Cast the input to Eigen types for math
  Eigen::VectorXd ea = Eigen::Map<Eigen::VectorXd>(sa.data(), sa.size());
  Eigen::VectorXd ey = Eigen::Map<Eigen::VectorXd>(sy.data(), sy.size());

  //Calculate error for each layer
  error[length-1] = ea - ey;
  for (int i = length-2; i > 0; i--) {
    error[i] = (theta_mat[i].transpose() * error[i+1]).cwiseProduct(activation_[i].cwiseProduct(Eigen::VectorXd::Ones(activation_[i].size()) - activation_[i]));
    
    //Remove the bias element for every layer but the first
    //TODO: Please tell me there a better way to do this in Eigen?
    if (i > 1) {
      error[i].segment(0, error[i].size()-1) = error[i].tail(error[i].size()-1);
      error[i].conservativeResize(error[i].size()-1);
    }
  }

  //Zero-out errors corresponding to zero inputs.
  //IMPORTANT: This step makes the network only update from non-zero observed outputs. Typical NN's do not do this.
  error[length-1].cwiseProduct(ey) / *std::max_element(sy.begin(), sy.end());
  
  for (int i = length-2; i >= 0; i--) {
    //Calculate gradients
    Eigen::MatrixXd grad = error[i+1] * activation_[i].transpose();

    //Remove the row of 1's from the last gradient
    if (i==0) {
      grad.block(0, 0, grad.rows()-1, grad.cols()) = grad.block(1, 0, grad.rows()-1, grad.cols());
      grad.conservativeResize(grad.rows()-1, grad.cols());
    }

    //Calculate partial derivatives
    Eigen::MatrixXd temp = theta_mat[i] * regularization_;
    temp.col(0) = Eigen::VectorXd::Zero(temp.cols());
    Eigen::MatrixXd derivative = grad + temp;

    //Update thetas
    theta_mat[i] = theta_mat[i] - learningRate_ * derivative;
  }

  //TODO: Does there need to be a step copying thetas back into the global vector?
}

void NeuralNet::propagateAndUpdate(const std::vector<double> &x, const std::vector<double> &y) {
  std::vector<double> a;
  propagate(x,a);
  update(x,y,a);
}

} // namespace NeuRL

