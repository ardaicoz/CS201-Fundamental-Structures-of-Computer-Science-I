#include "DoublyList.h"
using namespace std;

DoublyList::DoublyList() {
    size = 0;
    head = NULL;
}

DoublyList::DoublyList(const DoublyList& aDoublyList) {
    size = aDoublyList.size;

    if (aDoublyList.head == NULL)
        head = NULL;
    else {
        //copy first node
        head = new DoublyListNode;
        head->item = aDoublyList.head->item;
        head->prev = NULL;
        //copy rest of list
        DoublyListNode* newPtr = head; //new list ptr
        DoublyListNode* prevPtr = head; //next node's prev pointer will point to this address

        for (DoublyListNode* origPtr = aDoublyList.head->next; origPtr != NULL; origPtr = origPtr->next) {
            //created a new node
            newPtr->next = new DoublyListNode;
            //moved the pointer to this new node
            newPtr = newPtr->next;
            //transfering the item to this new node
            newPtr->item = origPtr->item;
            
            //prev pointer of this new node is now pointing to node before
            newPtr->prev = prevPtr;
            //iterate prev pointer
            prevPtr = prevPtr->next;
        }
        //at the end make the next pointer null
        newPtr->next = NULL;
    }
}

DoublyList::~DoublyList() {
    while ( !isEmpty() )
        remove(1);
}

bool DoublyList::isEmpty() const {
    return size == 0;
}

int DoublyList::getLength() const {
    return size;
}

DoublyList::DoublyListNode* DoublyList::find(const int index) const {
    if (index < 1 || index > getLength())
        return NULL;
    else {
        DoublyListNode* cur = head;

        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}

void DoublyList::retrieve(const int index, ListItemType2& dataItem) const {
    if ( index >= 1 && index <= getLength() ) {
        DoublyListNode* cur = find(index);
        dataItem = cur->item;
    }
}

void DoublyList::insert(const int index, ListItemType2 newItem) {
    int newLength = getLength() + 1;

    if (index >= 1 && index <= newLength) {
        //created a new node
        DoublyListNode* newPtr = new DoublyListNode;
        //set the new size and put this item to this node
        size = newLength;
        newPtr->item = newItem;

        if (index == 1) {
            //next pointer of this node will point to previously first node
            newPtr->next = head;
            //prev pointer will be NULL becuase index is 1
            newPtr->prev = NULL;
            //head pointer now point to this new node
            head = newPtr;
        }
        else {
            //get the address of node at the back
            DoublyListNode* prevNode = find(index-1);
            //new node's next pointer will now point to node that was previously in front of prev node
            newPtr->next = prevNode->next;
            //prev node's next pointer will now point to this new node (new node is fitted between these two nodes)
            prevNode->next = newPtr;
            //new node's prev pointer will now point to node that was previously in this index 
            newPtr->prev = prevNode;

            //if addition happens between two nodes (if index equals to newLength, addition happens in the very end), 
            //set the front node's prev pointer to new node
            if (index != newLength)
                newPtr->next->prev = newPtr;
        }
    }
}

void DoublyList::remove(const int index) {
    DoublyListNode* cur;

    if (index >= 1 && index <= getLength()) {
        --size;

        if (index == 1) {
            //temp pointer of cur now points to the first node (which is also pointed by "head")
            cur = head;
            //head pointer skips this node and points to the next node (this skipped node will be deleted)
            //cur pointer still points to the lonely node
            head = head->next;
            //disconnecting the next node from skipped node
            head->prev = NULL;
        }
        else {
            //get the address of the node at the back
            DoublyListNode* prev = find(index-1);
            //cur pointer now points to the node that is in front of prev node
            cur = prev->next;
            //prev node's next pointer skips the node in front of it and point to the next node
            prev->next = cur->next;
            //connecting the next node to prev node
            cur->next->prev = prev;
        }
        
        //in every case, cur pointer points to the node to be deleted
        //disconnecting this node from actual list
        cur->next = NULL;
        cur->prev = NULL;
        //deleting the node
        delete cur;
        cur = NULL;
    }
}

void DoublyList::display() const {
    if (size == 0) {
        cout << "DoublyList is empty" << endl;
    }
    else {
        cout << "[";
        for (DoublyListNode* temp = head; temp != NULL; temp = temp->next) {
            cout << (temp->item).getId() << " " << (temp->item).getFirstName() << (temp->item).getLastName() << " - ";
        }
        cout << "]" << endl;
    }
}