#include "SinglyList.h"
using namespace std;

SinglyList::SinglyList() {
    size = 0;
    head = NULL;
}

SinglyList::SinglyList(const SinglyList& aSinglyList) {
    size = aSinglyList.size;

    if (aSinglyList.head == NULL)
        head == NULL; //original list is empty
    else {
        //copy first node
        head = new SinglyListNode;
        head->item = aSinglyList.head->item;
        //copy rest of list
        SinglyListNode* newPtr = head; //new list ptr

        for (SinglyListNode* origPtr = aSinglyList.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new SinglyListNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}

SinglyList::~SinglyList() {
    while ( !isEmpty() )
        remove(1);
}

bool SinglyList::isEmpty() const {
    return size == 0;
}

int SinglyList::getLength() const {
    return size;
}

SinglyList::SinglyListNode* SinglyList::find(const int index) const {
    if (index < 1 || index > getLength())
        return NULL;
    else {
        SinglyListNode* cur = head;

        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}

void SinglyList::retrieve(const int index, ListItemType1& dataItem) const {
    if ( index >= 1 && index <= getLength() ) {
        SinglyListNode* cur = find(index);
        dataItem = cur->item;
    }
}

void SinglyList::insert(const int index, ListItemType1 newItem) {
    int newLength = getLength() + 1;

    if (index >= 1 && index <= newLength) {
        SinglyListNode* newPtr = new SinglyListNode;
        size = newLength;
        newPtr->item = newItem;

        if (index == 1) {
            newPtr->next = head;
            head = newPtr;
        }
        else {
            SinglyListNode* prev = find(index-1);
            newPtr->next = prev->next;
            prev->next = newPtr;
        }
    }
}

void SinglyList::remove(const int index) {
    SinglyListNode* cur;

    if (index >= 1 && index <= getLength()) {
        --size;

        if (index == 1) {
            cur = head;
            head = head->next;
        }
        else {
            SinglyListNode* prev = find(index-1);
            cur = prev->next;
            prev->next = cur->next;
        }
        
        cur->next = NULL;
        delete cur;
        cur = NULL;
    }
}

void SinglyList::display() const {
    if (size == 0) {
        cout << "SinglyList is empty" << endl;
    }
    else {
        cout << "[";
        for (SinglyListNode* temp = head; temp != NULL; temp = temp->next) {
            cout << (temp->item).getId() << ", " << (temp->item).getTitle() << " - ";
        }
        cout << "]" << endl;
    }
}

bool SinglyList::isExists(const ListItemType1 item) const {
    bool found = false;
    int id = item.getId();
    
    for (SinglyListNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == id) {
            found = true;
            return found;
        }
    }

    return found;
}

int SinglyList::findIndex(const ListItemType1 item) const {
    int id = item.getId();
    int index = 1;

    for (SinglyListNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == id) {
            return index;
        }
        index++;
    }

    return -1;
}

