#!/usr/bin/env bash
# Build the Gomoku GUI. Requires raylib installed under /usr/local.
set -e
g++ gomoku.cpp -o gomoku \
    -I/usr/local/include -L/usr/local/lib \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
echo "Built ./gomoku  —  run it with:  ./gomoku"
