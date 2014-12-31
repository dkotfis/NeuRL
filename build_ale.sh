#! /bin/bash

#TODO: This only currently works on Mac with Brew installed.

brew install sdl2
brew install sdl_gfx
brew install sdl_image

pushd external/ale_0.4-2.4/ale_0_4
cp makefile.mac makefile
make
cd doc/examples
make rlglueAgent
cd ../../
popd
