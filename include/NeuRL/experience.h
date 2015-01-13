#ifndef EXPERIENCE_H_
#define EXPERIENCE_H_

namespace NeuRL {

/*! An experience is a SARSA set. */
struct Experience {

  std::vector<double> s1;
  int a1;
  double r;
  std::vector<double> s2;
  int a2;

};

} // namespace NeuRL

#endif // EXPERIENCE_H_
