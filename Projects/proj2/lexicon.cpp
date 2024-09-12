#include <iostream>
#include "lexicon.h"

Lexicon::Lexicon()
{
    this->word_count = 0;
    this->capacity = 8;
    this->words = new std::string[this->capacity];
}

void Lexicon::push_back(std::string& s)
{
    this->words[this->word_count] = s;
    this->word_count++;
}

std::string& Lexicon::get(int index)
{
    return this->words[index];
}

int Lexicon::size()
{
    return this->word_count;
}

Lexicon::~Lexicon()
{
    delete[] this->words;
}