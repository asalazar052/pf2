#ifndef data_set
#define data_set
#include <vector>
#include <string>
using namespace std;

class Dataset{

    protected:
    //   col    name
        vector<string> col_names;

    //  matrix  row    cell
        vector< vector<string> > data;

    //  indxes col-idx pointer-to-row
        vector< vector< vector<string>* > > indices;

    public:
        Dataset();
        virtual ~Dataset(); 

        void load_csv(string& filename);
        void index_data();
        int col_count();
        int row_count();
        vector<string>& get_row(int i);
        void query(string& start, string& end, int& column);
        int binary_search(string target, int col_num);
        void print_index(int col_num);

};

#endif