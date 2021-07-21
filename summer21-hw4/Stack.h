#ifndef __STACK_H
#define __STACK_H
#include <iostream>

typedef int StackItemType;

class Stack {
public:
   Stack();
   Stack(const Stack& aStack);
   ~Stack();

   bool isEmpty() const;
   
   void push(StackItemType newItem);
   void pop();
   void pop(StackItemType& stackTop);
   
   void getTop(StackItemType& stackTop) const;
   StackItemType getTop() const;
   void display() const;

private:
   struct StackNode {            // a node on the stack
      StackItemType item;        // a data item on the stack
      StackNode    *next;        // pointer to next node
   };

   StackNode *topPtr;     // pointer to first node in the stack
};

#endif