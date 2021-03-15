//Arda Icoz
//21901443
//Section 1

#include "Stack.h"
using namespace std;

Stack::Stack() {
	topPtr = NULL;
}

Stack::Stack( const Stack& aStack ) {
	if ( aStack.topPtr == NULL ) {
		topPtr =  NULL;
	}
	else {
		topPtr = new StackNode;
		topPtr->item = aStack.topPtr->item;
		
		StackNode *newPtr = topPtr;
		for ( StackNode *originalPtr = aStack.topPtr->next; originalPtr != NULL; originalPtr = originalPtr->next ) {
			newPtr->next = new StackNode;
			newPtr = newPtr->next;
			newPtr->item = originalPtr->item;
		}
		newPtr->next = NULL;
	}
}

Stack::~Stack() {
	while ( !isEmpty() ) {
		pop();
	}
}

bool Stack::isEmpty() const {
	return topPtr == NULL;
}

bool Stack::push( StackItemType newItem ) {
	StackNode *newPtr = new StackNode;
	newPtr->item = newItem;
	newPtr->next = topPtr;
	topPtr = newPtr;
	return true;
}

bool Stack::pop() {
	if ( isEmpty() )
		return false;
	else {
		StackNode *temp = topPtr;
		topPtr = topPtr->next;
		temp->next = NULL;
		delete temp;
		return true;
	}
}

bool Stack::pop( StackItemType& stackTop ) {
	if ( isEmpty() ) {
		return false;
	}
	else {
		stackTop = topPtr->item;
		StackNode *temp = topPtr;
		topPtr = topPtr->next;
		
		temp->next = NULL;
		delete temp;
		return true;
	}
}

bool Stack::getTop( StackItemType& stackTop ) const {
	if ( isEmpty() ) {
		return false;
	}
	else {
		stackTop = topPtr->item;
		return true;
	}
}

//string Stack::getTop() const {
//	return topPtr->item;
//}