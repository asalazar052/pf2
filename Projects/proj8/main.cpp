#include <iostream>
#include <vector>
#include "config.h"
#include "charmatrix.h"
#include "linkedlist.h"
#include "dataset.h"

using namespace std;

vector<string> g_lex;
CharMatrix g_grid;
Dataset g_dataset;
extern int g_comparisons;



//Lexicon stuff
void fillLexicon(){

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
            for(unsigned int i = 0; i < g_lex.size(); i++){
                cout << i <<". " << g_lex[i] << endl;
            }
        }

        else{
            g_lex.push_back(word);

            if(!config.quiet){
                cout << "So far, the words you have entered are:" << endl;

                //outputs all values
                for (unsigned int i = 0; i < g_lex.size(); i++){
                    cout << i << ". " << g_lex[i] << endl;
                }
            }
        }
    }
}

//CharMatrix stuff
void loadCharMatrix(){
    if(!config.quiet){
        cout << "Please enter a grid of characters." << endl;
        cout << "All rows should ahve the same length." << endl;
        cout << "When you are done, just press Enter." << endl;
    }

    vector <string> grid;
    while(true){
        string row;
        getline(cin, row);

        if(row.compare("") == 0)
            break;
        if(grid.size() > 0 && row.size() != grid[0].size())
            throw runtime_error("Rows in a CharMatrix mist all have the same size!");

        grid.push_back(row);
    }

    int height = grid.size();
    int width = 0;
    if(height > 0)
        width = grid[0].size();
    g_grid.resize(width, height);

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            g_grid.put(x, y, grid[y][x]);
        }
    }
    

}

void printCharMatrix(){
    for (int y = 0; y < g_grid.height(); y++){
        for (int x = 0; x < g_grid.width(); x++){
            cout << g_grid.get(x, y);
        }
        cout << endl;
    }
}

//floodFill stuff
void fill(int x, int y, int c, int maxDepth){

    //recognizes the char that needs to be replaced
    char bef = g_grid.get(x, y);

    //checks to see if the currrent char is bef
    if(bef == c || maxDepth == 0)
        return;

    g_grid.put(x, y, c);

    //checks char to the left
    if(x > 0 && g_grid.get(x - 1, y) == bef)
        fill(x - 1, y, c, maxDepth - 1);
    
    //checks char above
    if(y > 0 && g_grid.get(x, y - 1) == bef)
        fill(x, y - 1, c, maxDepth - 1);
    
    //checks char to the right
    if(x + 1 < g_grid.width() && g_grid.get(x + 1, y) == bef)
        fill(x + 1, y, c, maxDepth - 1);
    
    //checks char below
    if(y + 1 < g_grid.height() && g_grid.get(x, y + 1) == bef){
        fill(x, y + 1, c, maxDepth - 1);
    }

    

}

void floodFill(){

    //gets starting x coordinate
    string word;
    if(!config.quiet){
        cout << "Please enter a starting column:" << endl;
        cout << "> ";
    }
    getline(cin, word);
    //string to integer
    int x = stoi(word);

    //gets starting y coordinate
    if(!config.quiet){
        cout << "Please enter a starting row:" << endl;
        cout << "> ";
    }

    getline(cin, word);
    int y = stoi(word);

    //gets the fill character
    if(!config.quiet){    
    cout << "Please enter a fillcharacter:" << endl;
    cout << "> ";
    }

    getline(cin, word);
    int c = word[0];

    if(!config.quiet){
        cout << "Please enter the max fill depth: " << endl;
    }

    getline(cin, word);
    int maxDepth = stoi(word);

    //recursive function

    //cout << "before seg fault" << endl;
    fill(x, y, c, maxDepth);
    //cout << "after seg fault" << endl;
}

//lexIndex is used to get g_lex word index, wordIndex is index of character
bool boggleSearch(int lexIndex, int x, int y, unsigned int wordIndex, CharMatrix v, bool* f){
    
    v.put(x, y, '#');

    string working = g_lex[lexIndex];

    if(working.length() - 1 == wordIndex){
        *f = true;
    }


    //normal bounds
    //right bound
    if((x + 1 < g_grid.width()) && (wordIndex + 1 < working.length()) && (v.get(x + 1, y) == working.at(wordIndex + 1))){
        //v.put(x + 1, y, '#');           
        boggleSearch(lexIndex, x + 1, y, wordIndex + 1, v, f);
    }

    //left bound
    if((x > 0) && (wordIndex + 1 < working.length()) && (v.get(x - 1, y) == working.at(wordIndex + 1))){
        //v.put(x - 1, y, '#');      
        boggleSearch(lexIndex, x - 1, y, wordIndex + 1, v, f);
     
    }

    //bottom bound
    if((y + 1 < g_grid.height()) && (wordIndex + 1 < working.length()) && (v.get(x, y + 1) == working.at(wordIndex + 1))){
        //v.put(x, y + 1, '#');
        boggleSearch(lexIndex, x, y + 1, wordIndex + 1, v, f);
    }

    //top bound
    if((y > 0) && (wordIndex + 1 < working.length()) && (v.get(x, y - 1) == working.at(wordIndex + 1))){
        //v.put(x, y - 1, '#');
        boggleSearch(lexIndex, x, y - 1, wordIndex + 1, v, f);
    }

    //diagonal bounds
    //top left
    if((x > 0) && (y > 0) && (wordIndex + 1 < working.length()) && (v.get(x - 1, y - 1) == working.at(wordIndex + 1))){
        //v.put(x - 1, y - 1, '#');      
        boggleSearch(lexIndex, x - 1, y - 1 , wordIndex + 1, v, f);
     
    }

    //top right
    if((x + 1 < g_grid.width()) && (y > 0) && (wordIndex + 1 < working.length()) && (v.get(x + 1, y - 1) == working.at(wordIndex + 1))){
        //v.put(x + 1, y - 1, '#');      
        boggleSearch(lexIndex, x + 1, y - 1 , wordIndex + 1, v, f);
     
    }

    //bottom right
    if((x + 1 < g_grid.width()) && (y + 1 < g_grid.height()) && (wordIndex + 1 < working.length()) && (v.get(x + 1, y + 1) == working.at(wordIndex + 1))){
        //v.put(x + 1, y + 1, '#');      
        boggleSearch(lexIndex, x + 1, y + 1 , wordIndex + 1, v, f);
     
    }

    //bottom left
    if((x > 0) && (y + 1 < g_grid.height()) && (wordIndex + 1 < working.length()) && (v.get(x - 1, y + 1) == working.at(wordIndex + 1))){
        //v.put(x - 1, y + 1, '#');      
        boggleSearch(lexIndex, x - 1, y + 1 , wordIndex + 1, v, f);
    }


    


    return *f;
}

void boggle(){

    CharMatrix visited;

    for(unsigned int i = 0; i < g_lex.size(); i++){
        for(int x = 0; x < g_grid.width(); x++){
            for(int y = 0; y < g_grid.height(); y++){
                if(g_grid.get(x, y) == g_lex[i].at(0)){
                    
                    bool* found = new bool(false);

                    CharMatrix visited = g_grid;
                    visited.put(x, y, '#');

                    if(boggleSearch(i, x, y, 0, visited, found)){

                        cout << g_lex[i] << endl;

                        y = g_grid.height();
                        x = g_grid.width();
                    }
                    delete(found);
                }
            }
        }
    }
}

//Dataset stuff
void load_csv()
{
    cout << "Please enter a filename of a .csv file:" << endl;
    cout << "> ";
    string filename;
    getline(std::cin, filename);
    g_dataset.load_csv(filename);
    g_dataset.index_data();
}

void query()
{
    // Ask for query parameters
    cout << "Please enter a column index:" << endl;
    cout << "> ";
    string column_str;
    getline(std::cin, column_str);
    int column = stoi(column_str);
    cout << "Please enter a starting value:" << endl;
    cout << "> ";
    string start;
    getline(std::cin, start);
    cout << "Please enter an ending value:" << endl;
    cout << "> ";
    string end;
    getline(std::cin, end);

    // Perform the query
    g_dataset.query(start, end, column); // (you will write this method)
}

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
            cout << "7. Linked List unit test" << endl;
            cout << "8. Merge Sort" << endl;
            cout << "9. Load CSV file" << endl;
            cout << "10. Query" << endl;
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

        //7th option
        else if(option.compare("7") == 0){

            unitTest();

        }

        //8th option
        else if(option.compare("8") == 0){
            LinkedList* list = new LinkedList();

            while(g_lex.size() > 0){
                list->push_front(g_lex.back());
                g_lex.pop_back();
            }
            //list->printList();
            //cout << endl;
            list->sort();
            //list->printList();

            while(list->size() > 0)
                g_lex.push_back(list->pop_front());

            //cout << "comparisons: " << g_comparisons << endl;
            
            cout << "comparisons: " << g_comparisons << endl;
        }
        
        //9th option
        else if(option.compare("9") == 0){
            load_csv();
        }
        
        //10th option
        else if(option.compare("10") == 0){
            query();
        }
        



        else {
            cout << option << " was not one of the options. Quitting." << endl;
            break;
        }
    }
}
