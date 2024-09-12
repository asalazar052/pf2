#include "charmatrix.h"
using std::string;

CharMatrix::CharMatrix(){
}

CharMatrix::~CharMatrix(){
}

//understand this
void CharMatrix::resize(int width, int height){
    this->chars.clear();
    for(int i = 0; i < height; i++){
        this->chars.push_back(string(width, ' ' ));
    }
}


//width and height
int CharMatrix::width(){
    if(height() == 0){
        return 0;
    }
    return this->chars[0].size();
}

int CharMatrix::height(){
    return this->chars.size();
}


//get
char CharMatrix::get(int x, int y){
    return this->chars[y][x];
}

//put
void CharMatrix::put(int x, int y, char c){
    this->chars[y][x] = c;
}

