#! /bin/bash

compBasePath=../external/15-rl-competition-2009
systemPath=$compBasePath/system
#Source a script that sets all important functions and variables
source $systemPath/rl-competition-includes.sh

#Utility functions from rl-competition-includes.sh
startEnvShellInBackGround

PYTHONPATH=../external/python-codec/src/:../external/15-rl-competition-2009/system/includes:../external/15-rl-competition-2009/trainers/consoleTrainerPython/src/:./src python mario/marioEnv.py 

#Utility functions from rl-competition-includes.sh
waitForEnvShellToDie