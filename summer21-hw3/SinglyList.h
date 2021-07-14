#ifndef __SINGLYLIST_H
#define __SINGLYLIST_H
#include <iostream>
#include "Course.h"

typedef Course ListItemType1;

class SinglyList {
public:
    SinglyList();
    SinglyList(const SinglyList& aSinglyList);
    ~SinglyList();

    bool isEmpty() const;
    int getLength() const;
    void retrieve(const int index, ListItemType1& dataItem) const;
    
    void insert(const int index, ListItemType1 newItem);
    void remove(const int index);

    //additional functions
    bool isExists(const ListItemType1 item) const;
    void display() const;
    int findIndex(const ListItemType1 item) const;

private:
    struct SinglyListNode {
        ListItemType1 item;
        SinglyListNode* next;
    };
    
    int size;
    SinglyListNode *head;

    SinglyListNode* find(const int index) const;
};

#endif