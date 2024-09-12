#ifndef functions_h
#define functions_h

#include "charmatrix.h"
#include <string>

using namespace std;

void fillLexicon();
void loadCharMatrix();
void printCharMatrix();
void fill(int x, int y, int c, int maxDepth);
void floodFill();
bool boggleSearch(int lexIndex, int x, int y, unsigned int wordIndex, CharMatrix v, bool* f);
void boggle();


#endif