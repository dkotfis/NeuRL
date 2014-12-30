
#include <algorithm>
#include <stdlib.h>

#include <NeuRL/neural_q.h>

namespace NeuRL {

NeuralQ::NeuralQ(int numActions, int inputSize, int maxExperiences, double gamma, double alpha, bool useSARSA) : numActions_(numActions), maxExperiences_(maxExperiences), gamma_(gamma), useSARSA_(useSARSA), probRemember_(0.1), numReplaySamples_(10) {

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

int NeuralQ::policy(const std::vector<double> &s) const {
  int act = -1;
  double max_val = 0.0;
  std::vector<double> q_vals = this->value(s);
  for (int i = 0; i < q_vals.size(); i++) {
    if (q_vals[i] > max_val) {
      max_val = q_vals[i];
      act = i;
    }
  }
  return act;
}

void NeuralQ::replayExperiences(int num) {
  //Use the default number of samples if not assigned
  if (num == 0) {
    num = numReplaySamples_;
  }

  //Don't do anything until enough experiences are in the pool
  if (expPool_.size() < num) {
    return;
  }

  //Get num random samples from the pool and retrain the network on them
  for (int i = 0; i < num; i++) {
    int r = rand() * expPool_.size() / RAND_MAX;
    update(expPool_[r]);
  }
}

void NeuralQ::rememberExperience(const std::vector<double> &s1, int a1, double r, const std::vector<double> &s2, int a2) {
  double r1 = (double) rand() / RAND_MAX;
  if (r1 < probRemember_) {
    if (expPool_.size() >= maxExperiences_) {
      int r2 = rand() * expPool_.size() / RAND_MAX;
      std::swap(expPool_[r2], expPool_.back());
      expPool_.pop_back();
    }
    Experience exp;
    exp.s1 = s1;
    exp.a1 = a1;
    exp.r = r;
    exp.s2 = s2;
    exp.a2 = a2;
    expPool_.push_back(exp);
  }
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
