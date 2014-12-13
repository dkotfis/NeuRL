#! /bin/bash

#Build RL-Glue Core
pushd external/rlglue-3.04
./configure
make
sudo make install
popd

#Build RL-Glue C Codec
pushd externl/c-codec-2.0
./configure
make
sudo make install
popd

#Build RL-Glue Python Codec
pushd external/python-codec/src
python setup.py install
popd

#Build RL 2009 Competition Software
pushd external/15-rl-competition-2009
bash install.bash
popd

