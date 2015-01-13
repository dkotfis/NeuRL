#ifndef NEURAL_NET_H_
#define NEURAL_NET_H_

#include <vector>
#include <Eigen/Dense>

namespace NeuRL {

class NeuralNet {

 public:
  
  NeuralNet(const std::vector<int> &layers, double epsilon = 0.154, double learningRate = 0.1);

  void propagate(const std::vector<double> &x, std::vector<double> &a) const;

  void update(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &a);

  void propagateAndUpdate(const std::vector<double> &x, const std::vector<double> &y);

 private:

  /*! The neural network weights, flattened into a single dimension. */
  std::vector<double> theta_;

  /*! The stored off layers from the last propagation */
  //TODO: This is bad practice... redo the API to make this unnecessary
  mutable std::vector<Eigen::VectorXd> activation_;

  /*! The size of each layer in the network */
  std::vector<int> layers_;

  /*! One-Half the interval around zero used for assigning the initial random weights. */
  double epsilon_;

  /*! Constant factor used to scale backpropagation changes to weights. */
  double learningRate_;

  /*! Regularization factor */
  double regularization_;

}; // class NeuralNet

} // namespace NeuRL

#endif // NEURAL_NET_H_
