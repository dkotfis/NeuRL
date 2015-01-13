
#include <vector>

#include <NeuRL/neural_q.h>

#include <rlglue/Agent_common.h>
#include <rlglue/utils/C/RLStruct_util.h>
#include <rlglue/utils/C/TaskSpec_Parser.h>

action_t* this_action = NULL;
taskspec_t* ts = NULL;

std::vector<double> last_state;
int last_act;

NeuRL::NeuralQ* q = NULL;

//Flag whether or not the agent should be actively learning its policy
bool freezeLearning = false;

//Exploration factor determines probability of acting randomly
double explore = 1.0;

//These must be defined elsewhere and are environment-specific
extern void actionDecoder(const int act, action_t* result);
extern int actionEncoder(const action_t act);
extern std::vector<double> stateEncoder(const observation_t obs);
extern void randomAction(action_t* result);
extern int numActs, stateDimX, stateDimY;

#include <iostream>

void agent_init(const char* task_spec)
{
  //Seed the randomness
  srand(0);
  srand48(0);

  //Create the Neural-Q function
  q = new NeuRL::NeuralQ(numActs, stateDimX*stateDimY);
}

const action_t *agent_start(const observation_t *this_observation) {

  /*
  //Manually define the task spec since the mario environment produces one that is invalid
  const char* temp = "VERSION RL-Glue-3.0 PROBLEMTYPE episodic DISCOUNTFACTOR 1 OBSERVATIONS INTS (0 1) DOUBLES (0.1 1.0) CHARCOUNT 1024 ACTIONS INTS (-1 1) (2 0 1)
  REWARDS (-10.0 100.0)";
  //Struct to hold the parsed task spec
  ts=(taskspec_t*)malloc(sizeof(taskspec_t));
  int decode_result = decode_taskspec( ts, temp );
  if(decode_result!=0){
    printf("Could not decode task spec, code: %d for task spec: %s\n",decode_result,temp);
    exit(1);
  }
  */
  //this_action = allocateRLStructPointer(getNumIntAct(ts),getNumDoubleAct(ts),0);
  this_action = allocateRLStructPointer(3, 0, 0);

  //Determine the policy for this state
  std::vector<double> state = stateEncoder(*this_observation);
  int act = q->policy(state);

  //Save off data to globals for use in the next iteration
  last_state = state;
  last_act = act;

  //Decode the resulting action
  actionDecoder(act, this_action);

  //Maybe use random action to explore
  if ((double)rand()/(double)RAND_MAX < explore) {
    randomAction(this_action);
  }

  return this_action;
}

const action_t *agent_step(double reward, const observation_t *this_observation) {

  //Determine the policy for this state
  std::vector<double> state = stateEncoder(*this_observation);
  int act = q->policy(state);

  if (!freezeLearning) { 
    //With some probability, remember this experience
    q->rememberExperience(last_state, last_act, reward, state, act);

    //Retrain the network off of the current set of experiences
    q->replayExperiences(10);
  }

  //Save off data to globals for use in the next iteration
  last_state = state;
  last_act = act;

  //Decode the resulting action
  actionDecoder(act, this_action);

  //Maybe use random action to explore
  if ((double)rand()/(double)RAND_MAX < explore) {
    randomAction(this_action);
  }

  return this_action;
}

void agent_end(double reward) {
  //Cleanup the action
  free(this_action);
}

void agent_cleanup() {
}

void agent_freeze() {
}

const char* agent_message(const char* inMessage) {

  if (strstr(inMessage, "freeze_learning") != NULL) {
    freezeLearning = true;
    return "message understood, policy frozen";
  }
  if (strstr(inMessage, "unfreeze_learning") != NULL) {
    freezeLearning = false;
    return "message understood, policy unfrozen";
  }
  /*
  if (inMessage->startswith("set_exploring")) {
    splitString = inMessage.split(" ");
    explore = float(splitString[1]);
    return "message understood, setting exploration factor";
  }
  if (inMessage->startswith("save_policy")) {
    splitString=inMessage.split(" ");
    saveQFun(splitString[1]);
    return "message understood, saving policy";
  }
  if (inMessage->startswith("load_policy")) {
    splitString=inMessage.split(" ");
    loadQFun(splitString[1]);
    return "message understood, loading policy";
  }
  */
  if (strstr(inMessage, "use_impactful_experiences") != NULL) {
    //q.use_impactful = true;
    return "message understood, using impactful experiences";
  }
  if (strstr(inMessage, "use_all_experiences") != NULL) {
    //q.use_impactful = false;
    return "message understood, using all experiences";
  }
  if (strstr(inMessage, "reset_q") != NULL) {
    delete q;
    q = new NeuRL::NeuralQ(numActs, stateDimX*stateDimY);
    return "message understood, reseting q-function";
  }
  return "unrecognized message";
}
