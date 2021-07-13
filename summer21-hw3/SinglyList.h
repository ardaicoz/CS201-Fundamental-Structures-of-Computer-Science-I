#ifndef __SINGLYLIST_H
#define __SINGLYLIST_H
#include <iostream>
#include "Course.h"

typedef Course ListItemType;

class SinglyList {
public:
    SinglyList();
    SinglyList(const SinglyList& aSinglyList);
    ~SinglyList();

    bool isEmpty() const;
    int getLength() const;
    void retrieve(const int index, ListItemType& dataItem) const;
    
    void insert(const int index, ListItemType newItem);
    void remove(const int index);

    //additional functions
    bool isExists(const ListItemType item) const;
    void display() const;
    int findIndex(const ListItemType item) const;

private:
    struct SinglyListNode {
        ListItemType item;
        SinglyListNode* next;
    };
    
    int size;
    SinglyListNode *head;

    SinglyListNode* find(const int index) const;
};

#endif