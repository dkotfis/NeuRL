#! /bin/bash

#TODO: This only currently works on Mac with Brew installed.

brew install scons

pushd external
tar xvf fceux-2.2.2.src.tar
cd fceux-2.2.2
scons GTK=0 LUA=0
cd ..
popd

