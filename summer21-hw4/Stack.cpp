#include "Stack.h"
using namespace std;

Stack::Stack() : topPtr(NULL) {}

Stack::Stack(const Stack& aStack) {
    if (aStack.topPtr == NULL)
        topPtr = NULL;  // original stack is empty

    else {
        // copy first node
        topPtr = new StackNode;
        topPtr->item = aStack.topPtr->item;

        // copy rest of stack
        StackNode *newPtr = topPtr;
        for (StackNode *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new StackNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}

Stack::~Stack() {
    while (!isEmpty())
        pop();
}

bool Stack::isEmpty() const {
    return topPtr == NULL;
}

void Stack::push(StackItemType newItem) {
    // create a new node
    StackNode *newPtr = new StackNode;

    // set data portion  of new node
    newPtr->item = newItem;

    // insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;
}

void Stack::pop() {
    if (!isEmpty()) {
        StackNode *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
    }
}

void Stack::pop(StackItemType& stackTop) {
    if ( !isEmpty() ) {
        stackTop = topPtr->item;
        StackNode *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
    }
}

void Stack::getTop(StackItemType& stackTop) const {
    if ( !isEmpty() )
        stackTop = topPtr->item;
}

StackItemType Stack::getTop() const {
    StackItemType type;
    
    if ( !isEmpty() )
        type = topPtr->item;

    return type;
}

void Stack::display() const {
    for (StackNode* temp = topPtr; temp != NULL; temp = temp->next) {
        cout << temp->item << " ";
    }
    cout << endl;
}



