#! /bin/bash

#Build RL-Glue Core
pushd external/rlglue-3.04
./configure
make
make install
popd

#Build RL-Glue C Codec
pushd externl/c-codec-2.0
./configure --with-rl-glue=/usr/local
make
make install
popd

#Build RL-Glue Python Codec
pushd external/python-codec/src
python setup.py install
popd

#TODO: Do we need the java codec?

ldconfig
