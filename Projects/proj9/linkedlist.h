#ifndef linked_list
#define linked_list
#include <string>
#include "instancecounter.h"

using namespace std;


class LinkedListNode;

class LinkedList : public InstanceCounter{
    protected:
        LinkedListNode* first;
        LinkedListNode* last;
        int length;
    public:
        LinkedList();
        virtual ~LinkedList();
        //push
        void push_back(string& s);
        void push_front(string& s);

        //pop
        string pop_front();
        LinkedListNode* pop_front_node();

        //other
        void printList();
        int size();
        LinkedList* split(int n);
        void assumptions();
        LinkedList* merge(LinkedList& list2);
        void sort();

};

class LinkedListNode : public InstanceCounter{
    friend class LinkedList;
    protected: 
        LinkedListNode* next;
        string value;
    
    public:
        LinkedListNode(string& s);
        virtual ~LinkedListNode();
};

void unitTest();


#endif