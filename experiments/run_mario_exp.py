"""This script launches all of the processes necessary to train a
deep Q-network on Mario.

Usage:

run_mario_exp.py [--glue_port GLUE_PORT]

"""
import subprocess
import sys
import os
import argparse

# Check for glue_port command line argument and set it up...
parser = argparse.ArgumentParser(description='Mario RL Agent.')
parser.add_argument('--glue_port', type=str, default="4096",
                    help='rlglue port (default 4096)')
args, unknown = parser.parse_known_args()
my_env = os.environ.copy()
my_env["RLGLUE_PORT"] = args.glue_port
my_env["PYTHONPATH"] = '../external/python-codec/src/:../src/'

# Start the necessary processes:
p1 = subprocess.Popen(['rl_glue'], env=my_env) #RL-Glue
p2 = subprocess.Popen(['java', '-Xmx128M', '-jar', '../external/infinite_mario/mario.jar'], env=my_env) #Mario Environment
p3 = subprocess.Popen(['python', 'mario/marioExp.py'], env=my_env) #Experiment
p4 = subprocess.Popen(['python', 'mario/marioAgent.py'], env=my_env) #Neural Q Agent

p1.wait()
p2.wait()
p3.wait()
p4.wait()
