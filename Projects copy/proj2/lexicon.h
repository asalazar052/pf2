#ifndef lexicon_h
#define lexicon_h

#include <iostream>


// A data structure that holds words
class Lexicon
{
protected:

    //words that lexicon collects
    std::string* words;
    int word_count;
    int capacity;

//accesstible in other files
public:
    Lexicon();
    virtual ~Lexicon();
    void push_back(std::string& s);
    std::string& get(int index);
    int size();
    
};

#endif