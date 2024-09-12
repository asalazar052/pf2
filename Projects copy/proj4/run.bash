
#!/bin/bash
set -e
g++ -Wall -g main.cpp config.cpp charmatrix.cpp -o lex
./lex $*