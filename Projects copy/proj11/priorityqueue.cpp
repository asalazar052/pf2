#include "priorityqueue.h"
#include <iostream>


extern int smart_compare(string& a, string& b);

PriorityQueue::PriorityQueue(){
    //puts garbage in the 0 index
    this->heap.push_back("");
}

void PriorityQueue::check(){
    for(int index = 2; index < (int)this->heap.size(); index++){
        int parent = index / 2;
        if(smart_compare(this->heap[index], this->heap[parent]) < 0)
            throw runtime_error("heap property not exhibited");
    }
}

PriorityQueue::~PriorityQueue(){
}

void PriorityQueue::insert(string val){
    this->heap.push_back(val);
    int end = this->heap.size() - 1;
    this->swim(end);

    this->check();
}

void PriorityQueue::swim(int index){
    if(index / 2 == 0)
     return;

    int parent = index / 2;
    if(smart_compare(this->heap[index], this->heap[parent]) < 0){
        swap(this->heap[index], this->heap[parent]);
        swim(parent);
    }
}

string PriorityQueue::pop_first(){
    string return_val = this->heap[1];

    sink(1);



    this->check();

    return return_val;
}

void PriorityQueue::sink(int parent){

    if(this->heap.size() == 1)
        throw runtime_error("Negative index");

    int child1;
    int child2;

    while(parent * 2 < (int)this->heap.size() - 1){

        child1 = parent * 2;
        child2 = child1 + 1;


        //left comes before right
        if(smart_compare(this->heap[child1], this->heap[child2]) < 0){

            this->heap[parent] = this->heap[child1];
            parent = child1;
        }
        //right comes before left
        else{
            this->heap[parent] = this->heap[child2];
            parent = child2;
        }

    }

    //cout << "Parent: " << parent << endl;
    this->heap[parent] = this->heap[this->heap.size() - 1];
    this->swim(parent);
    this->heap.pop_back();

}

void PriorityQueue::print(){
    cout << endl;
    for(unsigned int i = 1; i < this->heap.size(); i++){
        cout << i << this->heap[i] << endl;
    }
    cout << endl;
};

