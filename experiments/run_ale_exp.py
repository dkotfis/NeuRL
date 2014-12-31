"""This script launches all of the processes necessary to train a
deep Q-network on an Atari 2600 game in ALE.

It currently is hooked up only to a default agent, not deep 
Q-learning

ALE must be built first with SDL enabled. The desired game ROM
must be added to the roms directory.

Usage:

run_ale_exp.py [--rom ROM_FILENAME] [--glue_port GLUE_PORT]

"""
import subprocess
import sys
import os
import argparse

# Check for glue_port command line argument and set it up...
parser = argparse.ArgumentParser(description='ALE RL Agent.')
parser.add_argument('--glue_port', type=str, default="4096",
                    help='rlglue port (default 4096)')
# Check for rom name.
parser.add_argument('--rom', type=str, default="pitfall",
                    help='rom file name (default pitfall)')

args, unknown = parser.parse_known_args()

my_env = os.environ.copy()
my_env["RLGLUE_PORT"] = args.glue_port

# Start the necessary processes:
p1 = subprocess.Popen(['rl_glue'], env=my_env) #RL-Glue
p2 = subprocess.Popen(['../external/ale_0.4-2.4/ale_0_4/ale', '-display_screen', 'true', '-game_controller', 'rlglue', '../roms/'+args.rom+'.bin'], env=my_env) #ALE Environment
p3 = subprocess.Popen(['../external/ale_0.4-2.4/ale_0_4/doc/examples/RLGlueExperiment'], env=my_env) #Experiment
p4 = subprocess.Popen(['../external/ale_0.4-2.4/ale_0_4/doc/examples/RLGlueAgent'], env=my_env) #Default Agent

p1.wait()
p2.wait()
p3.wait()
p4.wait()
