"""This script launches all of the processes necessary to train a
deep Q-network on an NES game.

It currently is hooked up only to launch the NES emulator environment.
The environment needs to be made compatible with RL-Glue.

Usage:

run_nes_exp.py [--rom ROM_FILENAME] [--glue_port GLUE_PORT]

"""
import subprocess
import sys
import os
import argparse

# Check for glue_port command line argument and set it up...
parser = argparse.ArgumentParser(description='NES RL Agent.')
parser.add_argument('--glue_port', type=str, default="4096",
                    help='rlglue port (default 4096)')
# Check for rom name.
parser.add_argument('--rom', type=str, default="smb3",
                    help='rom file name (default pitfall)')

args, unknown = parser.parse_known_args()

my_env = os.environ.copy()
my_env["RLGLUE_PORT"] = args.glue_port

# Start the necessary processes:
p1 = subprocess.Popen(['rl_glue'], env=my_env) #RL-Glue
p2 = subprocess.Popen(['../external/fceux-2.2.2/bin/fceux', '--xscale', '2', '--yscale', '2', '../roms/'+args.rom+'.nes'], env=my_env) #NES Environment
#p3 = subprocess.Popen([''], env=my_env) #Experiment
#p4 = subprocess.Popen([''], env=my_env) #Default Agent

p1.wait()
p2.wait()
#p3.wait()
#p4.wait()
