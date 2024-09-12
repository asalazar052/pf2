
#!/bin/bash
set -e
g++ -Wall -Werror -g  main.cpp config.cpp charmatrix.cpp linkedlist.cpp -o main
./main $*