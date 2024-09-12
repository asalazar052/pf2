
#!/bin/bash
set -e
g++ -Wall -Werror -g  main.cpp config.cpp charmatrix.cpp linkedlist.cpp dataset.cpp instancecounter.cpp priorityqueue.cpp -o main
valgrind ./main $*