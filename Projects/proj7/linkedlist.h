#ifndef linked_list
#define linked_list
#include <string>

using namespace std;


class LinkedListNode;

class LinkedList{
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

class LinkedListNode{
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