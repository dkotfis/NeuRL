
//#include <Eigen/Dense>

#include <NeuRL/neural_net.h>
#include <NeuRL/activation_functions.h>

namespace NeuRL {

NeuralNet::NeuralNet(const std::vector<int> &layers, double epsilon, double learningRate) : epsilon_(epsilon), learningRate_(learningRate), regularization_(0.1) {

  for (int i = 0; i < layers.size(); i++) {
    layers_.push_back(layers[i]);
  }

}

void NeuralNet::propagate(const std::vector<double> &x, std::vector<double> &a) const {

  int length = layers_.size();

  //std::vector<MatrixXf> theta_mat;

  int flag = 0;
  for (int i = 0; i < length-1; i++) {
    int size = layers_[i+1] * (layers_[i]+1);
    //theta_mat[i] = ;
    flag = flag + size;
  }

}

void NeuralNet::update(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &a) {

}

void NeuralNet::propagateAndUpdate(const std::vector<double> &x, const std::vector<double> &y) {
  std::vector<double> a;
  propagate(x,a);
  update(x,y,a);
}

} // namespace NeuRL

