#!/bin/bash
set -e
g++ main.cpp -o count
./count $*