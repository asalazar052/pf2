#include <iostream>
#include <vector>
#include "config.h"
#include "charmatrix.h"
#include "functions.h"



extern vector<string> g_lex;
extern CharMatrix g_grid;

using namespace std;

//Entry point
int main(int argc, char** argv)
{
    
    config.parse_flags(argc, argv);
    log("---Running in debug mode---");

    while (true){

        

        //print statements
        if(!config.quiet){

            for (int i = 0; i < 5; i++){
            cout << endl;
            }
            
            cout << "Adrian Salazar's PF2 projects" << endl << endl;
            cout << "Lexicon size: " << g_lex.size() << endl << endl;
            cout << "0. Quit" << endl;
            cout << "1. Fill lexicon" << endl;
            cout << "2. Tear Down Lexicon" << endl;
            cout << "3. Load char matrix" << endl;
            cout << "4. Print char matrix" << endl;
            cout << "5. Flood fill" << endl;
            cout << "6. Boggle" << endl;
            cout << "> ";

            for (int i = 0; i < 5; i++){
                cout << endl;
            }
        }
        
    
        string option;
        getline(cin, option);

        //quit option
        if (option.compare("0") == 0) {
            break;
        } 

        //1st option
        else if (option.compare("1") == 0) {
            fillLexicon();
        } 

        //2nd option
        else if (option.compare("2") == 0){
            
            while (g_lex.size() > 0){
                cout << g_lex[g_lex.size() - 1] << endl;
                g_lex.pop_back();
            }

        }

        //3rd option
        else if (option.compare("3") == 0){
            loadCharMatrix();
        }

        //4th option
        else if (option.compare("4") == 0){
            printCharMatrix();
        }

        //5th option
        else if(option.compare("5") == 0){
            floodFill();
        }

        //6th option
        else if(option.compare("6") == 0){
            if(!(g_lex.size() > 0 && g_grid.height() > 0)){
                cout << "Lexicon and/or CharMatrix not filled" << endl;
            }
            else{
                boggle();
            }
        }
        else {
            cout << option << " was not one of the options. Quitting." << endl;
            break;
        }

    }
}
