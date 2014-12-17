
#include <vector>

#include <NeuRL/neural_q.h>

#include <rlglue/Agent_common.h>
#include <rlglue/utils/C/RLStruct_util.h>
#include <rlglue/utils/C/TaskSpec_Parser.h>

action_t* this_action = NULL;
taskspec_t* ts = NULL;

NeuRL::NeuralQ* q = NULL;

bool freezeLearning = false;

//These must be defined elsewhere and are environment-specific
extern action_t actionDecoder(const int act);
extern int actionEncoder(const action_t act);
extern std::vector<double> stateEncoder(const observation_t obs);
extern int numActs, stateDimX, stateDimY;

void agent_init(const char* task_spec)
{
  //Seed the randomness
  srand(0);
  srand48(0);
  
  //Struct to hold the parsed task spec
  ts=(taskspec_t*)malloc(sizeof(taskspec_t));
  int decode_result = decode_taskspec( ts, task_spec );
  if(decode_result!=0){
    printf("Could not decode task spec, code: %d for task spec: %s\n",decode_result,task_spec);
    exit(1);
  }
  this_action=allocateRLStructPointer(getNumIntAct(ts),getNumDoubleAct(ts),0);

  //Create the Neural-Q function
  q = new NeuRL::NeuralQ(numActs, stateDimX*stateDimY);
}

const action_t *agent_start(const observation_t *this_observation) {
  return this_action;
}

const action_t *agent_step(double reward, const observation_t *this_observation) {
  return this_action;
}

void agent_end(double reward) {
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
    exp = float(splitString[1]);
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
