#!/usr/bin/bash
mkdir -p build && cd build
cmake .. && make
rm -fr ../execs
mkdir -p ../execs  
mv tic-tac-toe ../execs 
mv unit_tests ../execs