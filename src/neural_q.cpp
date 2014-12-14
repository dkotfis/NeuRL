
#include <NeuRL/neural_q.h>

namespace NeuRL {

NeuralQ::NeuralQ(int numActions, int inputSize, int maxExperiences, double gamma, double alpha, bool useSARSA) : maxExperiences_(maxExperiences), gamma_(gamma), useSARSA_(useSARSA) {

  //Create 2 hidden layers
  //TODO: Support customization of hidden layer topology
  int l[4] = {inputSize, (numActions+inputSize)/2, (numActions+inputSize)/2, numActions};
  std::vector<int> layers(&l[0], &l[0] + 4);
  nn_ = new NeuralNet(layers, 0.154, alpha);

}

std::vector<double> NeuralQ::value(const std::vector<double> &s, int a) const {
  std::vector<double> result;
  nn_->propagate(s, result);
  if (a != -1) {
    double val = result[a];
    result.clear();
    result.push_back(val);
  }
  return result;
}

void NeuralQ::replayExperiences(int num) {

}

void NeuralQ::rememberExperience(const std::vector<double> &s1, int a1, double r, const std::vector<double> &s2, int a2) {

}

void NeuralQ::update(const Experience &exp) {
  double val;
  if (useSARSA_) {
    val = exp.r + gamma_ * value(exp.s2, exp.a2).front();
  } else {
    std::vector<double> q = value(exp.s2);
    val = exp.r + gamma_ * *max_element(q.begin(), q.end());
  }
  std::vector<double> a(numActions_, 0.0);
  a[exp.a1] = val;
  nn_->propagateAndUpdate(exp.s1, a);
}

} //namespace NeuRL
