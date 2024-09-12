
#!/bin/bash
set -e
g++ -Wall -Werror -g main.cpp config.cpp charmatrix.cpp functions.cpp -o main
./main $*