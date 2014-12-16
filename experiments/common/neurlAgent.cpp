
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
//#include <assert.h>
#include "neurlAgent.h"
#include <rlglue/utils/C/RLStruct_util.h>
#include <rlglue/utils/C/TaskSpec_Parser.h>

namespace NeuRL {

} // namespace NeuRL

action_t* this_action=0;
taskspec_t *ts=0;
void randomify();

void agent_init(const char* task_spec)
{
  	srand(0);/*seed the randomness*/
	srand48(0);
  
	/*Struct to hold the parsed task spec*/
	ts=(taskspec_t*)malloc(sizeof(taskspec_t));
	int decode_result = decode_taskspec( ts, task_spec );
	if(decode_result!=0){
		printf("Could not decode task spec, code: %d for task spec: %s\n",decode_result,task_spec);
		exit(1);
	}
	this_action=allocateRLStructPointer(getNumIntAct(ts),getNumDoubleAct(ts),0);
}
const action_t *agent_start(const observation_t *this_observation) {
	randomify();
	return this_action;
}

const action_t *agent_step(double reward, const observation_t *this_observation) {
	randomify();
	return this_action;
}

void agent_end(double reward) {
}

void agent_cleanup() {
}

void agent_freeze() {
}

const char* agent_message(const char* inMessage) {
	return "Zero agent does not respond to messages.";
}

void randomify(){
	int i;
	for (i=0;i<this_action->numInts;i++) {
			this_action->intArray[i] = rand()%(getIntActMax(ts,i)+1-getIntActMin(ts,i)) +getIntActMin(ts,i);
		}
	for (i=0;i<this_action->numDoubles;i++) {
			this_action->doubleArray[i] = drand48()*(getDoubleObsMax(ts,i)-getDoubleObsMin(ts,i)) +getDoubleObsMin(ts,i);
		}
}
