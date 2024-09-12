#ifndef lexicon_h
#define lexicon_h

#include <iostream>

using std::string;


// A data structure that holds words
class Lexicon
{
protected:

    //words that lexicon collects
    std::string* words;
    int word_count;
    

//accesstible in other files
public:
    Lexicon();
    
    int capacity;;
    virtual ~Lexicon();
    void push_back(std::string& s);
    string& get(int index);
    int size();
    string back();
    void pop_back();

    
};

#endif