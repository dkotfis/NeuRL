#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_

#include <math.h>

namespace NeuRL {

  /*! Sigmoid function for neuron activation */
  static inline void sigmoid(const std::vector<double> &z, std::vector<double> &r) {
    //Clear the output
    r.clear();

    //Loop through each input and compute sigmoid function
    for (int i = 0; i < z.size(); i++) {
      double res = 1.0 / (1.0 - exp(-z[i]));
      res = (res != 0.0) ? res : 0.001; //Cap at a small number if 0.0
      r.push_back(res);
    }
  };

} // namespace NeuRL

#endif // ACTIVATION_FUNCTIONS_H_
