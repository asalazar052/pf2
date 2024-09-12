#include "linkedlist.h"
#include <iostream>


LinkedList::LinkedList(){
    this->first = nullptr;
    this->last = nullptr;
}

LinkedList::~LinkedList(){
    
}

LinkedListNode::LinkedListNode(string& s){
    this->next = nullptr;
    value = s;
}

LinkedListNode::~LinkedListNode(){
}



int LinkedList::size(){
    return this->length;
}

//******************METHODS******************

//push
void LinkedList::push_back(string& s){
    this->assumptions();
    LinkedListNode* new_node = new LinkedListNode(s);


    if(!this->first){
        this->first = new_node;
    }
    else{
        this->last->next = new_node;
    }
    this->last = new_node;
    length++;

    this->assumptions();
    
}

void LinkedList::push_front(string& s){
    this->assumptions();

    LinkedListNode* new_node = new LinkedListNode(s);
    if(!this->first){
        push_back(s);
        length--;
    }
    else{
        new_node->next = this->first;
        this->first = new_node;
    }

    length++;

    this->assumptions();
}

//pop
string LinkedList::pop_front(){
    this->assumptions();

    if(length == 0)
        throw runtime_error("Negative size");

    LinkedListNode* temp = nullptr;
    string s = this->first->value;

    if(this->first != this->last){
        temp = this->first;
        this->first = this->first->next;
        temp->next = nullptr;
        delete(temp);
    }
    else{
        this->first = nullptr;
        this->last = nullptr;
    }

    length--;

    this->assumptions();

    return s;
}

void LinkedList::printList(){
    this->assumptions();
    LinkedListNode* current = this->first;

    while(current){
        cout << current->value << endl;
        current = current->next;
    }   

    this->assumptions();
}


LinkedList* LinkedList::split(int n){

    LinkedList* second = new LinkedList();

    if(n > this->size() || n < 0)
        throw runtime_error("Out of bounds");

    for(int i = 0; i < n; i++){
        string s = this->pop_front();
        second->push_back(s);
    }

    return second;

}

void LinkedList::assumptions(){

    if(this->first && !this->last)
        throw runtime_error("There is a first but no last");
    if(this->last && !this->first)
        throw runtime_error("There is a last but no first");

    if(this->last){
        if(this->last->next != nullptr)
            throw runtime_error("next pointer within last ptr shoul be null");
    }
    if(length == 0 && this->first != nullptr)
        throw runtime_error("Empty list with allocated first pointer");
    
    
    if(length == 0 && this->last != nullptr)
        throw runtime_error("Empty list with allocated last pointer");


    if(length < 0)
        throw runtime_error("Negative size");
    
    
    if(length != this->size()){
        throw runtime_error("length does not equal size()");
    }

}

void unitTest(){
    string s1 = "Hello";
    string s2 = "my";
    string s3 = "name";
    string s4 = "is";
    string s5 = "Adrian";

    string a1 = "alpha";
    string a2 = "beta";
    string a3 = "gamma";
    string a4 = "delta";

    LinkedList* test = new LinkedList();
    test->push_back(s1);
    test->push_back(s2);
    test->push_back(s3);
    test->push_back(s4);
    test->push_back(s5);

    cout << endl;

    test->pop_front();
    test->pop_front();
    test->pop_front();
    test->pop_front();
    test->pop_front();
    

    test->push_front(a1);
    test->push_front(a2);
    test->push_front(a3);
    test->push_front(a4);
    test->push_back(s5);
    test->push_front(s1);
    test->push_back(a2);



    test->printList();
    cout << test->size() << endl;
    cout << endl;

    LinkedList* second = test->split(test->size() / 2);

    test->printList();
    cout << test->size() << endl;
    cout << endl;
    second->printList();
    cout << second->size() << "\n" << endl;

    cout << "passed" << endl;    
}