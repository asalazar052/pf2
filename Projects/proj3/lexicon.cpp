#include <iostream>
#include "lexicon.h"

using std::cout;
using std::endl;
using std::string;

Lexicon::Lexicon()
{
    this->word_count = 0;
    this->capacity = 8;
    this->words = new string[this->capacity];
}

void Lexicon::push_back(string& s)
{
    if(this->word_count == this->capacity - 1){
        
        //working
        string* new_words = new string[this->capacity * 2];

        for(int i = 0; i < this->word_count; i++){
            new_words[i] = this->words[i];
        }
        
        
        //cout << this->capacity << endl;
        //problem. losing new word at this point
        delete[] this -> words;
        this->words = new_words;

        this->capacity = this->capacity * 2;
        
    }

    //cout << word_count << endl;
    this->words[this->word_count] = s;
    this->word_count++;

}

string& Lexicon::get(int index)
{
    if(index < 0){
        throw std::runtime_error("Expected a non-negative index. Got " + std::to_string(index));
    }
    if(index >= this->word_count){
        throw std::runtime_error("Expected index (" + std::to_string(index) + ") to be less than word_count (" + std::to_string(this->word_count) + ")");
    }
    return this->words[index];
}

string Lexicon::back(){
    return get(word_count - 1);
}

void Lexicon::pop_back(){
        
    if(this->word_count <=0 ){
        throw std::runtime_error("word_count cannot be less than 0");
    }
    this->word_count--;

    

}

int Lexicon::size()
{
    return this->word_count;
}

Lexicon::~Lexicon()
{
    delete[] this->words;
}