#ifndef __DOUBLYLIST_H
#define __DOUBLYLIST_H
#include <iostream>
#include "Student.h"

typedef Student ListItemType2;

class DoublyList {
public:
    DoublyList();
    DoublyList(const DoublyList& aSinglyList);
    ~DoublyList();

    bool isEmpty() const;
    int getLength() const;
    void retrieve(const int index, ListItemType2& dataItem) const;
    
    void insert(const int index, ListItemType2 newItem);
    void remove(const int index);

    //additional functions
    //bool isExists(const ListItemType item) const;
    void display() const;
    //int findIndex(const ListItemType item) const;

private:
    struct DoublyListNode {
        ListItemType2 item;
        DoublyListNode* next;
        DoublyListNode* prev;
    };
    
    int size;
public: DoublyListNode *head;
    
    DoublyListNode* find(const int index) const;

};

#endif