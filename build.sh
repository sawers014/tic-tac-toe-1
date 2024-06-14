#!/bin/bash

set -xe

flags="-Wall -Wextra -ggdb -I./raylib-5.0_macos/include"
libs="-Wl,-rpath,./raylib-5.0_macos/lib/ -L./raylib-5.0_macos/lib -lraylib -lm -ldl"

cc $flags main.c -o ./build/tic-tac-toe $libs
