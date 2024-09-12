#include "dataset.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std; 

extern int smart_compare(std::string& a, std::string& b);

int g_col = 0;

string strip(const string value)
{
    string s = value;
    while (s.size() > 0 && std::isspace(s[s.size() - 1]))
        s.erase(s.end() - 1);
    while (s.size() > 0 && std::isspace(s[0]))
        s.erase(s.begin());
    return s;
}

bool custom_less(vector<string>* a, vector<string>* b){
    
    string a_val = strip((*a)[g_col]);
    string b_val = strip((*b)[g_col]);

    return smart_compare(a_val, b_val) < 0;
}

vector<string>& Dataset::get_row(int i){
    return data[i];
}

Dataset::Dataset(){

}

Dataset::~Dataset(){
}

void Dataset::load_csv(string& filename)
{
    // Clear any existing data
    this->data.clear();

    // Open the file
    ifstream stream;
    stream.open(filename);
    if (!stream.is_open()) {
        throw system_error(errno, generic_category(), filename);
    }

    // Read the file
    while (!stream.eof())
    {
        // Read a line
        string s;
        if (!getline(stream, s))
            break;
        vector<string> empty;
        this->data.push_back(empty);
        vector<string>& current_row = this->data.back();

        // Break up the line into cells
        while (true)
        {
            // Find the next comma
            size_t pos = s.find(",");
            if (pos == string::npos)
            {
                // This is the last cell in the row
                current_row.push_back(s);
                break;
            }
            else
            {
                // This is not the last cell in the row
                current_row.push_back(s.substr(0, pos));
                s.erase(0, pos + 1); // erase the cell and the comma
            }
        }

        // Ensure all rows have the same size
        if (current_row.size() < 1)
        {
            // This row is empty, so just drop it
            this->data.pop_back();
        }
        else if (current_row.size() != this->data[0].size())
        {
            // Uh oh, the row is the wrong size!
            string s = "Error, row " + to_string(this->data.size());
            s += " has " + to_string(current_row.size());
            s += " elements. Expected " + to_string(this->data[0].size());
            throw runtime_error(s);
        }
    }

    // Move the first row into this->col_names
    this->col_names = this->data[0];
    this->data.erase(this->data.begin());
}

int Dataset::col_count(){
    return data[0].size();
}

int Dataset::row_count(){
    return data.size();
}


void Dataset::index_data()
{
    // Index the data
    indices.clear();
    indices.resize(this->col_count());

    for(int i = 0; i < this->col_count(); i++)
    {
        // Build an index for column i
        vector< vector<string>* >& index = indices[i];
        for (int j = 0; j < this->row_count(); j++)
            index.push_back(&this->data[j]);

        g_col = i;
        sort(index.begin(), index.end(), custom_less);
    }
}

int Dataset::binary_search(string target, int col_num){

    vector< vector<string>* > index = this->indices[col_num];
    int floor = 0;
    int ceil = this->row_count();
    int row_num;

    while(true){
        row_num = (floor + ceil) / 2;
        if(row_num == floor)
            break;
        string data_val = strip((*index[row_num])[col_num]);
        int cmp = smart_compare(data_val, target);

        if (cmp < 0)
            floor = row_num;
        else
            ceil = row_num;
    }
    
    //cout << "Row Num: " << row_num << endl;
    // fine-tune the row_num
    string data_val = strip((*index[row_num])[col_num]);
    //cout << data_val << endl;
    while (row_num > 0 && smart_compare(data_val, target) >= 0){
        row_num--;
        data_val = strip((*index[row_num])[col_num]);
    }
    while (row_num < row_count() && smart_compare(data_val, target) < 0){
        row_num++;
        data_val = strip((*index[row_num])[col_num]);
    }
        
    //cout << "final: " << row_num << endl;
    return row_num;
}

void Dataset::query(string& start, string& end, int& column){

    vector< vector<string>* > index = this->indices[column];
    int row = binary_search(start, column);
    string curr = strip((*index[row])[column]);

    while(smart_compare(curr, end) < 0){
        
        vector<string> row_data = *index[row];
        for(unsigned int j = 0; j < row_data.size(); j++){
            cout << row_data[j] << ",";
        }
        cout << endl;
        row++;
        curr = strip((*index[row])[column]);
        

    }

    // for(int i = 0; i < row - 1; i++){
    //     //string data_val = strip((*index[row + i])[column]);
    //     vector<string> row_data = *index[row + i];
    //     for(int j = 0; j < row_data.size(); j++){
    //         cout << row_data[j] << endl;
    //     }

    // }
     
}

void Dataset::print_index(int col_num){
    cout << "Sorted by column " << col_num << ":" << endl;
    cout << "-------------------" << endl;
    
    vector< vector<string>*> index = this->indices[col_num];
    for (size_t i = 0; i < index.size(); i++)
    {
        vector<string>& row = *index[i];
        for (size_t j = 0; j < row.size(); j++)
        {
            if (j > 0)
                cout << ", ";
            cout << row[j];
        }
        cout << endl;
    }
}

