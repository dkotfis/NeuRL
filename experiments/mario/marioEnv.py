#!/usr/bin/python

# Mario Environment Loader

import random
import rlglue.RLGlue as RLGlue
import matplotlib.pyplot as plt
from consoleTrainerHelper import *

def trainAgent():
        episodesToRun = 10000
        totalSteps = 0
	exp = 1.0
	raw_results = []
        for i in range(episodesToRun):
		#loadMario(True, True, i % 100, 0, 1, 0)
		if (i % 100 == 0):
			if (exp > 0.1):
				exp -= 0.05
			RLGlue.RL_agent_message("set_exploring " + str(exp)) 
                RLGlue.RL_episode(2000)
		thisSteps = RLGlue.RL_num_steps()
                print "Total steps in episode %d is %d" %(i, thisSteps)
                thisReturn = RLGlue.RL_return()
                print "Total return in episode %d is %f" %(i, thisReturn)
		raw_results.append(thisReturn)
                totalSteps += thisSteps
        print "Total steps : %d\n" % (totalSteps)
        RLGlue.RL_agent_message("save_policy agents/expertAgent.dat") 

def demoAgent():
        episodesToRun = 10000
	totalSteps = 0
	RLGlue.RL_agent_message("load_policy agents/expertAgent.dat")
        RLGlue.RL_agent_message("freeze learning");
	RLGlue.RL_agent_message("set_exploring 1.0")
        for i in range(episodesToRun):
		loadMario(False, False, i % 100, 0, 1, 0)
                RLGlue.RL_episode(2000)
                thisSteps = RLGlue.RL_num_steps()
                print "Total steps in episode %d is %fd" %(i, thisSteps)
                thisReturn = RLGlue.RL_return()
                print "Total return in episode %d is %f" %(i, thisReturn)
                totalSteps += thisSteps
        print "Total steps : %d\n" % (totalSteps)

def main():
	whichTrainingMDP = 0
        '''
	Parameter definition:
	fast - determines if Mario runs very fast or at playable-speed. Set it to true to train your agent, false if you want to actually see what is going on.
	dark - make Mario visible or not. Set it to true to make it invisible when training.
	levelSeed - determines Marios behavior 
	levelType - 0..2: outdoors/subterranean/other
	levelDifficulty - 0..10, how hard it is. 
	instance - 0..9, determines which Mario you run.	
	'''
	loadMario(False, False, 0, 0, 1, whichTrainingMDP)

	RLGlue.RL_init()

	trainAgent()
	#demoAgent()

	RLGlue.RL_cleanup()

if __name__ == "__main__":
	main()
