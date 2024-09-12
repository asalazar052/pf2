#ifndef priority_queue
#define priority_queue

#include <vector>
#include <string>
using namespace std;


class PriorityQueue{

    public:
        vector<string> heap;

        PriorityQueue();
        virtual ~PriorityQueue();

        //helpers
        void check();
        void print();

        //functions
        void swim(int index);
        void sink(int parent);
        void insert(string val);
        string pop_first();
};

#endif
