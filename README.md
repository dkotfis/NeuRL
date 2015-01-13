NeuRL
=====

Neural-Network Reinforcement Learning Library


##Setup

To run demonstrations with the NeuRL library, Rl-Glue and the 2009 AI Competition software must be installed. These are included in the 'external' directory for convenience. These files can be installed from the project home directory with:
```bash
$ sudo ./setup.sh
```

##Building

The C++ source code for the project can be built with CMake. To do this from the home directory:
```bash
mkdir build
cd build
cmake ..
make
```

##Running Demo Experiments

Demonstration experiments are in the 'experiments' directory. They can be run with python executables, eg:
```bash
$ python run_mario_exp.py
```

##Roadmap

- C++ Implementation of Neural Q-Learning
- Customizable Experience Weighting
- GPU-Acceleration with cuDNN
- Atari ALE Experiments
