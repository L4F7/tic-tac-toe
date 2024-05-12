#!/usr/bin/bash
mkdir -p build && cd build
cmake .. && make
./tic-tac-toe