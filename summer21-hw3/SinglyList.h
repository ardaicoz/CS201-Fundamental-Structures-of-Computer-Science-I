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
    bool retrieve(const int index, ListItemType& dataItem) const;
    bool insert(const int index, ListItemType newItem);
    bool remove(const int index);

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