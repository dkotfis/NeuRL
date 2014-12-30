
#include "mario_agent.h"

int numActs = 12;
int stateDimX = 20;
int stateDimY = 12;

void actionDecoder(const int act, action_t* result) {
  result->intArray[0] = (int) ((double)act / 4.0) - 1;
  result->intArray[1] = (int) ((double)act / 2.0) % 2;
  result->intArray[2] = act %2;
  return;
}

int actionEncoder(const action_t act) {
  return act.intArray[2] + 2*act.intArray[1] + 4*(act.intArray[0]+1);
}

std::vector<double> stateEncoder(const observation_t obs) {
  std::vector<double> s;
  return s;
}

void randomAction(action_t* result) {
  result->intArray[0] = (int)((double)rand()*3.0/(double)RAND_MAX) - 1;
  //Mario's random actions are bias towards moving to the right
  if ((double)rand()/(double)RAND_MAX < 0.5) {
    result->intArray[0] = 1;
  }
  result->intArray[1] = (int)((double)rand()/(double)RAND_MAX + 0.5);
  result->intArray[2] = (int)((double)rand()/(double)RAND_MAX + 0.5);
  return;
}

//--------------------------------------------------------

coord getMario(const observation_t obs) {
  coord xy;
  return xy;
}

std::vector<coord> getMonsters(const observation_t obs) {
  std::vector<coord> xys;
  return xys;
}

