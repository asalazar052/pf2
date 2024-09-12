#include "linkedlist.h"
#include <iostream>
#include <cstring>

int g_comparisons = 0;

int smart_compare(string& a, string& b);

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

//pop_node
LinkedListNode* LinkedList::pop_front_node(){

    LinkedListNode* front = nullptr;

    if(length == 0)
        throw runtime_error("Negative size");

    
    if(this->first != this->last){
        front = this->first;
        this->first = this->first->next;
        front->next = nullptr;
    }
    else{
        this->first = nullptr;
        this->last = nullptr;
    }
    
    length--;

    return front;
    
}

//other

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

    //returns first half
    return second;

}

LinkedList* LinkedList::merge(LinkedList& firstHalf){
    this->assumptions();
    LinkedList* mergedList = new LinkedList();
    //int comparison;

    while(this->size() > 0 || firstHalf.size() > 0){
        if(this->size()>0 && firstHalf.size() > 0){
            if(smart_compare(this->first->value, firstHalf.first->value) < 0){
                string s = this->pop_front();
                mergedList->push_back(s);
            }
            else{
                string s = firstHalf.pop_front();
                mergedList->push_back(s);
            }
        }
        else if(this->size() > 0){
            while(this->size() > 0){
                string s = this->pop_front();
                mergedList->push_back(s);
            }
        }
        else{
            while(firstHalf.size() > 0){
                string s = firstHalf.pop_front();
                mergedList->push_back(s);
            }
        }
    }

    this->assumptions();
       
    return mergedList;

}

void LinkedList::sort(){

    
    LinkedList* firstHalf = this->split(this->size() / 2);

    if(this->size() > 1){
        this->sort();
    }
    
    if(firstHalf->size() > 1){
        firstHalf->sort();
    }

    *this = *(this->merge(*firstHalf));

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
    // string s1 = "Hello";
    // string s2 = "my";
    // string s3 = "name";
    // string s4 = "is";
    // string s5 = "Adrian";

    // string a1 = "alpha";
    // string a2 = "beta";
    // string a3 = "gamma";
    // string a4 = "delta";

    // LinkedList* test = new LinkedList();
    // test->push_back(s1);
    // test->push_back(s2);
    // test->push_back(s3);
    // test->push_back(s4);
    // test->push_back(s5);

    // cout << endl;

    // test->pop_front();
    // test->pop_front();
    // test->pop_front();
    // test->pop_front();
    // test->pop_front();
    

    // test->push_front(a1);
    // test->push_front(a2);
    // test->push_front(a3);
    // test->push_front(a4);
    // test->push_back(s5);
    // test->push_front(s1);
    // test->push_back(a2);



    // test->printList();
    // cout << test->size() << endl;
    // cout << endl;

    // LinkedList* second = test->split(test->size() / 2);

    // test->printList();
    // cout << test->size() << endl;
    // cout << endl;
    // second->printList();
    // cout << second->size() << "\n" << endl;

    // cout << "passed" << endl;    
}

int smart_compare(std::string& a, std::string& b) {
    g_comparisons++;
    // Skip the parts that are the same
    unsigned int i = 0;
    while(i < a.size() && i < b.size() && a[i] == b[i]) {
        i++;
    }
    if (i >= a.size()) {
        if (i >= b.size()) {
            return 0;
        } else {
            return -1;
        }
    } else if (i >= b.size()) {
        return 1;
    }

    // Skip zeros
    unsigned int a_start = i;
    unsigned int b_start = i;
    while (a_start < a.size() && a[a_start] == '0')
        a_start++;
    while (b_start < b.size() && b[b_start] == '0')
        b_start++;

    // Count digits
    unsigned int a_digits = a_start;
    while (a_digits < a.size() && a[a_digits] >= '0' && a[a_digits] <= '9')
        a_digits++;
    unsigned int b_digits = b_start;
    while (b_digits < b.size() && b[b_digits] >= '0' && b[b_digits] <= '9')
        b_digits++;
    if (a_digits > 0 && a_digits < b_digits) {
        return -1; // a comes first because its number is shorter
    } else if (b_digits > 0 && b_digits < a_digits) {
        return 1; // b comes first because its number is shorter
    } else {
        // The numbers are the same length, so compare alphabetically
        return strcmp(a.c_str() + a_start, b.c_str() + b_start);
    }
}