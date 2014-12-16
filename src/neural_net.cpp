
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

  //TODO: Finish this function
}

void NeuralNet::propagateAndUpdate(const std::vector<double> &x, const std::vector<double> &y) {
  std::vector<double> a;
  propagate(x,a);
  update(x,y,a);
}

} // namespace NeuRL

