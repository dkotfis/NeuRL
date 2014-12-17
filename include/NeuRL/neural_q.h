#ifndef NEURAL_Q_H_
#define NEURAL_Q_H_

#include <NeuRL/neural_net.h>
#include <NeuRL/experience.h>

namespace NeuRL {

class NeuralQ {

 public:

  NeuralQ(int numActions, int inputSize, int maxExperiences = 500, double gamma = 0.6, double alpha = 0.2, bool useSARSA = false);

  /*! Destructor cleans up memory */
  ~NeuralQ() {
    delete nn_;
  };

  /*! Gets the Q-Value of a state/action pair. If the action is not given, it defaults to all actions. */
  std::vector<double> value(const std::vector<double> &s, int a = -1) const;

  /*! Draws experiences from the pool and trains the network on them. Defaults to 0, which uses the default number. */
  void replayExperiences(int num = 0);

  void rememberExperience(const std::vector<double> &s1, int a1, double r, const std::vector<double> &s2, int a2);

 private:

  /*! Used to update the underlying neural network from an experience. */
  void update(const Experience &exp);

  /*! Neural network object that will be used to represent the Q-function. */
  NeuralNet* nn_;

  /*! The pool of experiences that is being remembered. */
  std::vector<Experience> expPool_;

  int numActions_;

  int maxExperiences_;

  double gamma_;

  bool useSARSA_;

  /*! The probability of remembering an experience. */
  //TODO: Should this be an input option in the constructor?
  double probRemember_;

  /*! The number of experiences that are drawn from the pool and retrained when calling experience replay. */
  int numReplaySamples_;

}; // class NeuralQ

} // namespace NeuRL

#endif // NEURAL_Q_H_
