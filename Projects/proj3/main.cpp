#include <iostream>
#include "config.h"
#include "lexicon.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

Lexicon g_lex;


// Count from 0 to n-1
void count(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << i << " ah-ah-ah!" << endl;
    }
}

void fill_lexicon(){

    while(true){

        if(!config.quiet){
        
            //space
            for (int i = 0; i < 5; i++){
                cout << endl;
            }
            
            //prompts user
            cout << "Please enter another word" << endl;
            cout << "> ";
        }
        
        //creates word and assigns input
        string word;
        getline(cin, word);

        if (word.size() == 0){
            break;
        }
        
        if(word.compare("-") == 0){
            g_lex.pop_back();
            for(int i = 0; i < g_lex.size(); i++){
                cout << i <<". " << g_lex.get(i) << endl;
            }
        }

        else{
            g_lex.push_back(word);

            if(!config.quiet){
                cout << "So far, the words you have entered are:" << endl;

                //outputs all values
                for (int i = 0; i < g_lex.size(); i++){
                    cout << i << ". " << g_lex.get(i) << endl;
                }
            }
        }
    }
}

//Entry point
int main(int argc, char** argv){
    
    config.parse_flags(argc, argv);
    log("---Running in debug mode---");

    while (true){

        for (int i = 0; i < 5; i++){
            cout << endl;
        }

        //print statements
        cout << "Adrian Salazar's PF2 projects" << endl << endl;
        cout << "Lexicon size: " << g_lex.size() << endl << endl;
        cout << "0. Quit" << endl;
        cout << "1. Fill lexicon" << endl;
        cout << "2. Tear Down Lexicon" << endl;
        cout << "> ";
    
        string option;
        getline(cin, option);

        //quit option
        if (option.compare("0") == 0) {
            break;
        } 

        //1st option
        else if (option.compare("1") == 0) {
            fill_lexicon();
        } 

        //2nd option
        else if (option.compare("2") == 0){
            
            while (g_lex.size() > 0){
                cout << g_lex.get(g_lex.size() - 1) << endl;
                g_lex.pop_back();
            }

        }
        else {
            cout << option << " was not one of the options. Quitting." << endl;
            break;
        }

    }
}
