#include "Book.h"
#include <iostream>
using namespace std;

Book::Book( const int bookId, const std::string bookTitle, const int bookYear ) {
	if ( bookId > 0 ) 
		this->bookId = bookId;
	
	this->bookTitle = bookTitle;
	
	if ( bookYear > 0 )
		this->bookYear = bookYear;
		
	checked = false;
}

Book::~Book() {
	
}

int Book::getBookId() {
	return bookId;
}

string Book::getBookTitle() {
	return bookTitle;
}

int Book::getBookYear() {
	return bookYear;
}

bool Book::isChecked() {
	return checked;
}

void Book::setChecked( bool checked ) {
	this->checked = checked;
}

