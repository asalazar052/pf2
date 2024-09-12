
#!/bin/bash
set -e
g++ -Wall -g main.cpp config.cpp lexicon.cpp -o main
./main $*