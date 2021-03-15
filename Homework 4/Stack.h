//Arda Icoz
//21901443
//Section 1

#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <string>

typedef std::string StackItemType;

class Stack {
public:
	Stack();
	Stack( const Stack& aStack );
	~Stack();
	
	bool isEmpty() const;
	bool push( StackItemType newItem );
	bool pop();
	bool pop( StackItemType& stackTop );
	bool getTop( StackItemType& stackTop ) const;
	//std::string getTop() const;

private:
	struct StackNode {
		StackItemType item;
		StackNode *next;
	};
	
	StackNode *topPtr;
};

#endif // STACK_H
