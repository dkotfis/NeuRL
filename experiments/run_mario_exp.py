"""This script launches all of the processes necessary to train a
deep Q-network on Mario.

Usage:

run_mario_exp.py [--glue_port GLUE_PORT]

All unrecognized command line arguments will be passed on to
mario_agent.py

Adapted from

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


# Start the necessary processes:
p1 = subprocess.Popen(['rl_glue'], env=my_env)
p2 = subprocess.Popen(['./mario/mario_environment.sh'], env=my_env)
p3 = subprocess.Popen(['../build/mario_agent'], env=my_env)

p1.wait()
p2.wait()
p3.wait()
