#!/bin/bash
find . -name "*.java" -print | xargs javac -sourcepath src -cp RLVizLib.jar -d classes
jar cf mario.jar -C classes .
