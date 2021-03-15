#include "Student.h"
#include <string>
#include <iostream>
using namespace std;

Student::Student( const string stuName, const int stuId ) {
	studentName = stuName;
	
	if ( stuId > 0 )
		studentId = stuId;
		
	size = 0;
	head = NULL;
}

Student::~Student() {
	while ( getListSize() > 0 ) {
		removeCheckedBookList();
	}
}

string Student::getName() {
	return studentName;
}

int Student::getId() {
	return studentId;
}

int Student::getListSize() {
	return size;
}

void Student::deleteCheckedBook( const int bookId ) {
	CheckedBook* current;
	
	if ( findCheckedBook(bookId) == size - 1 ) {
		current = head;
		head = head->next;
	}
	else {
		int index = findCheckedBook(bookId); //now "current" pointer has this node
		current = retrieveCheckedBookWithIndex(index);
		CheckedBook* prev = retrieveCheckedBookWithIndex(index-1);
		prev->next = current->next;
	}
	current->next = NULL;
	delete current;
	current = NULL;
	size--;
}

int Student::findCheckedBook( const int bookId ) {
	CheckedBook *iter = head;
	int index = 0;
		
	while ( iter != NULL ) {
		if ( iter->bookItem.getBookId() == bookId ) {
			return index;
		}
		index++;
		iter = iter->next;
	}
	return -1;
}

Student::CheckedBook* Student::retrieveCheckedBookWithIndex( const int index ) {
	CheckedBook* nodeToReturn = head;
	
	for ( int i = 0; i < index; i++ ) { 
		nodeToReturn = nodeToReturn->next;
	}
	return nodeToReturn;
}

void Student::addCheckedBook( const int bookId, const string bookName, const int bookYear ) {
	if ( size == 0 ) {
		//creating the node and initializing it
		CheckedBook *book = new CheckedBook();
		book->bookItem = Book( bookId, bookName, bookYear );
		book->next = NULL;
		
		//setting headStudent pointer to the new node
		head = book;
		size++;
	}
	else {
		if ( findCheckedBook(bookId) == -1 ) { // if it returns -1 that means the book isn't in the list
			//creating the node and initializing it
			CheckedBook *book = new CheckedBook();
			book->bookItem = Book( bookId, bookName, bookYear );
			book->next = NULL;
			
			//setting the pointer of the last node to the new one
			retrieveCheckedBookWithIndex(size-1)->next = book;
			++size;
		}
	}
}

bool Student::checkedBookExists( const int bookId ) const {
	CheckedBook *iter = head;
	
	while ( iter != NULL ) {
		if ( iter->bookItem.getBookId() == bookId ) {
			return true;
		}
		iter = iter->next;
	}
	return false;
}

void Student::removeCheckedBookList() {
	CheckedBook* current;
	
	//pointing the headStudent to the next node
	current = head;
	head = head->next;
	
	//deleting the first node in the list
	current->next = NULL;
	delete current;
	current = NULL;
	
	size--;
}

int Student::getCheckedBookId( const int index ) {
	return retrieveCheckedBookWithIndex(index)->bookItem.getBookId();
}

string Student::getCheckedBookTitle( const int index ) {
	return retrieveCheckedBookWithIndex(index)->bookItem.getBookTitle();
}

int Student::getCheckedBookYear( const int index ) {
	return retrieveCheckedBookWithIndex(index)->bookItem.getBookYear();
}
