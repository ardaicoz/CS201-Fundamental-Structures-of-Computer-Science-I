#include "LibrarySystem.h"
#include <iostream>
#include <iomanip> 
using namespace std;

LibrarySystem::LibrarySystem() {
	sizeStudentList = 0;
	headStudent = NULL;
	
	sizeBookList = 0;
	headBook = NULL;
}

LibrarySystem::~LibrarySystem() {
	while ( !bookListIsEmpty() ) 
		removeBookList();
	
	while ( !studentListIsEmpty() ) 
		removeStudentList();
}

void LibrarySystem::checkoutBook( const int bookId, const int studentId ) {
	if ( !bookExists(bookId) && searchBookInEveryStudent(bookId) ) {
		cout << "Book " << bookId << " has been already checked by another student" << endl;
	}
	else if ( !bookExists(bookId) && !searchBookInEveryStudent(bookId) ) {
		cout << "Book " << bookId << " does not exist for checkout" << endl;
	} 
	else if ( !studentExists(studentId) ) {
		cout << "Student " << studentId << " does not exist" << endl;
	}
	else {		
		retrieveStudent(studentId)->studentItem.addCheckedBook( retrieveBook(bookId)->bookItem.getBookId(), retrieveBook(bookId)->bookItem.getBookTitle(), retrieveBook(bookId)->bookItem.getBookYear() );
	
		//deleting the book from Library System
		deleteBookWithoutMsg(bookId);
		
		cout << "Book " << bookId << " has been checked out by student " << studentId << endl;
	}
}

void LibrarySystem::returnBook( const int bookId ) {
	if ( bookExists(bookId) ) {
		cout << "Book " << bookId << " has not been checked out" << endl;
	}
	else {
		StudentNode* iter = headStudent;
		
		//deleting this book from the student who checked out
		//but first we need to search for every student to find who checked out 
		while ( iter != NULL ) {
			if ( iter->studentItem.checkedBookExists(bookId) ) {
				//and before deleting, we need to add it to library
				int index = iter->studentItem.findCheckedBook(bookId);
				addBookWithoutMsg( iter->studentItem.getCheckedBookId(index), iter->studentItem.getCheckedBookTitle(index), iter->studentItem.getCheckedBookYear(index) );
				
				//now we can delete it from student
				iter->studentItem.deleteCheckedBook(bookId);
				break;
			}
			iter = iter->next;
		}
	}
}

void LibrarySystem::showAllBooks() const {
	BookNode* iterBook = headBook;
	StudentNode* iterStu = headStudent;
	
	cout << "Book id\t" << "Book name\t" << "Year\t" << "Status" << endl;
	
	//listing books in LibrarySystem
	while ( iterBook != NULL ) {
		showBook( iterBook->bookItem.getBookId() );
		iterBook = iterBook->next;

	}
	
	//listing books that have been checked out by other students
	while ( iterStu != NULL ) {
		for ( int i = 0; i < iterStu->studentItem.getListSize(); i++ ) {
			showBook( iterStu->studentItem.getCheckedBookId(i) );
		}
		iterStu = iterStu->next;
	}
}

void LibrarySystem::showBook(const int bookId) const {
	if ( !bookExists(bookId) && !searchBookInEveryStudent(bookId) ) {
		cout << "Book " << bookId << " does not exists" << endl;
	}
	else {
		if ( bookExists(bookId) ) {
			cout <<  retrieveBook(bookId)->bookItem.getBookId() << "\t" << retrieveBook(bookId)->bookItem.getBookTitle() << "\t" << retrieveBook(bookId)->bookItem.getBookYear() << "\t";
			cout << "Not checked out" << endl;
		}
		else {
			StudentNode* iter = headStudent;
			
			while ( iter != NULL ) {
				if ( iter->studentItem.checkedBookExists(bookId) ) {
					int index = iter->studentItem.findCheckedBook(bookId);
					cout << iter->studentItem.getCheckedBookId(index) << "\t" << iter->studentItem.getCheckedBookTitle(index) << "\t" << iter->studentItem.getCheckedBookYear(index) << "\t";
					cout << "Checked out by student " << iter->studentItem.getId() << endl;
					break;
				}
				iter = iter->next;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////STUDENT FUNCTIONS///////////////////////////////////////////////////
void LibrarySystem::addStudent( const int studentId, const string studentName ) {
	if ( studentListIsEmpty() ) {
		//creating the node and initializing it
		StudentNode *student = new StudentNode();
		student->studentItem = Student( studentName, studentId );
		student->next = NULL;
		
		//setting headStudent pointer to the new node
		headStudent = student;
		sizeStudentList++;
		cout << "Student " << studentId << " has been added" << endl;
	}
	else {
		//checking if studentId already exists
		if ( studentExists(studentId) ) {
			cout << "Student " << studentId << " already exists" << endl;
		}
		else {
			//creating the node and initializing it
			StudentNode *student = new StudentNode();
			student->studentItem = Student( studentName, studentId );
			student->next = NULL;
			
			//setting the pointer of the last node to the new one
			retrieveStudentWithIndex(sizeStudentList-1)->next = student;
			++sizeStudentList;
			cout << "Student " << studentId << " has been added" << endl;
		}
	}
}

void LibrarySystem::showStudent( const int studentId ) const {
	if ( !studentExists(studentId) ) {
		cout << "Student " << studentId << " does not exits" << endl;
	}
	else {
		StudentNode* studentToShow = retrieveStudent(studentId);	
		cout << "Student id: " << studentId << " student name: " << studentToShow->studentItem.getName() << endl;
		
		if ( studentToShow->studentItem.getListSize() == 0 ) {
			cout << "Student " << studentId << " has no books" << endl;
		}
		else {
			cout << "Student " << studentId << " has checked out following books:" << endl;
			cout << "Book id\t " << " Book name\t " << " Year" << endl;
			
			for ( int i = 0; i < studentToShow->studentItem.getListSize(); i++ ) {
				cout << studentToShow->studentItem.getCheckedBookId(i) << "\t" << studentToShow->studentItem.getCheckedBookTitle(i) << "\t" << studentToShow->studentItem.getCheckedBookYear(i) << endl;
			}
		}
	}
}

void LibrarySystem::deleteStudent( const int studentId ) {
	if ( studentListIsEmpty() ) {
		cout << "There are no students in this LibrarySystem." << endl;
	}
	else {
		if ( !studentExists(studentId) ) {
			cout << "Student " << studentId << " does not exist" << endl;
		}
		else {
			//firstly, we have to know which books does this student have
			//then we have to set "checked" to false for these books in LS's book list (to indicate that they are ready to be reserved)
			BookNode* iter = headBook;
			
			while ( iter != NULL ) {
				if ( retrieveStudent(studentId)->studentItem.checkedBookExists(iter->bookItem.getBookId()) ) { //asking to student: "do you have this book?"
					iter->bookItem.setChecked(false); //"if you have, now you don't"
				}
				iter = iter->next;
			}
			
			//after returning all the books to LibrarySystem (making "checked" to false), we can continue with deleting the student
			StudentNode* current;
			if ( findStudent(studentId) ==  0 ) {
				current = headStudent;
				headStudent = headStudent->next;
			}
			else {
				int index = findStudent(studentId); //now "current" pointer has this node
				current = retrieveStudentWithIndex(index);
				StudentNode* prev = retrieveStudentWithIndex(index-1);
				prev->next = current->next;
			}
			current->next = NULL;
			delete current;
			current = NULL;
			sizeStudentList--;
			cout << "Student " << studentId << " has been deleted" << endl;
		}
	}
}

bool LibrarySystem::studentExists( const int studentId ) const {
	StudentNode *iter = headStudent;
	
	while ( iter != NULL ) {
		if ( iter->studentItem.getId() == studentId ) {
			return true;
		}
		iter = iter->next;
	}
	return false;
}

bool LibrarySystem::studentListIsEmpty() {
	return (sizeStudentList == 0);
}

int LibrarySystem::studentListGetLength() {
	return sizeStudentList;
}

int LibrarySystem::findStudent( const int studentId ) {
	if ( !studentExists(studentId) ) {
		return -1;
	}
	else {
		StudentNode *iter = headStudent;
		int index = 0;

		while ( iter != NULL ) {
			if ( iter->studentItem.getId() == studentId ) {
				return index;
			}
			index++;
			iter = iter->next;
		}
		return -1;
	}
}

void LibrarySystem::printList() {
	StudentNode* iter = headStudent;
	
	while ( iter != NULL ) {
		cout << iter->studentItem.getId() << endl;
		iter = iter->next;
	}
	cout << "sizeStudentList: " << sizeStudentList << endl;
}

LibrarySystem::StudentNode* LibrarySystem::retrieveStudent( const int studentId ) const {
	StudentNode* iter = headStudent;
	StudentNode* nodeToReturn;

	while ( iter != NULL ) {
		if ( iter->studentItem.getId() == studentId ) {
			nodeToReturn = iter;
		}
		iter = iter->next;
	}
	return nodeToReturn;
}

LibrarySystem::StudentNode* LibrarySystem::retrieveStudentWithIndex( const int index ) {
	StudentNode* nodeToReturn = headStudent;
	
	for ( int i = 0; i < index; i++ ) { 
		nodeToReturn = nodeToReturn->next;
	}
	return nodeToReturn;
}

void LibrarySystem::removeStudentList() {
	StudentNode* current;
	
	//pointing the headStudent to the next node
	current = headStudent;
	headStudent = headStudent->next;
	
	//deleting the first node in the list
	current->next = NULL;
	delete current;
	current = NULL;
	
	sizeStudentList--;
}

bool LibrarySystem::searchBookInEveryStudent( const int bookId ) const {
	bool exists = false;
	int count = 0;
	StudentNode* iter = headStudent;
	
	while ( iter != NULL ) {
		if ( iter->studentItem.checkedBookExists(bookId) ) {
			exists = true;
		}
		else {
			count++;
		}
		iter = iter->next;
	}
	if ( count == sizeStudentList )
		exists = false;
	
	return exists;
}

///////////////////////////////////////////////////BOOK FUNCTIONS///////////////////////////////////////////////////////////////////////
bool LibrarySystem::bookListIsEmpty() {
	return (sizeBookList == 0);
}

bool LibrarySystem::bookExists( const int bookId ) const {
	BookNode *iter = headBook;
	
	while ( iter != NULL ) {
		if ( iter->bookItem.getBookId() == bookId ) {
			return true;
		}
		iter = iter->next;
	}
	return false;
}

LibrarySystem::BookNode* LibrarySystem::retrieveBookWithIndex( const int index ) {
	BookNode* nodeToReturn = headBook;
	
	for ( int i = 0; i < index; i++ ) { 
		nodeToReturn = nodeToReturn->next;
	}
	return nodeToReturn;
}

void LibrarySystem::addBook( const int bookId, const string bookName, const int bookYear ) {
	if ( bookListIsEmpty() ) {
		//creating the node and initializing it
		BookNode *book = new BookNode();
		book->bookItem = Book( bookId, bookName, bookYear );
		book->next = NULL;
		
		//setting headStudent pointer to the new node
		headBook = book;
		sizeBookList++;
		cout << "Book " << bookId << " has been added" << endl;
	}
	else {
		//checking if bookId already exists
		if ( bookExists(bookId) ) {
			cout << "Book " << bookId << " already exists" << endl;
		}
		else {
			//creating the node and initializing it
			BookNode *book = new BookNode();
			book->bookItem = Book( bookId, bookName, bookYear );
			book->next = NULL;
			
			//setting the pointer of the last node to the new one
			retrieveBookWithIndex(sizeBookList-1)->next = book;
			++sizeBookList;
			cout << "Book " << bookId << " has been added" << endl;
		}
	}
}

void LibrarySystem::addBookWithoutMsg( const int bookId, const string bookName, const int bookYear ) {
	if ( bookListIsEmpty() ) {
		//creating the node and initializing it
		BookNode *book = new BookNode();
		book->bookItem = Book( bookId, bookName, bookYear );
		book->next = NULL;
		
		//setting headStudent pointer to the new node
		headBook = book;
		sizeBookList++;
		cout << "Book " << bookId << " has been returned" << endl;
	}
	else {
		//creating the node and initializing it
		BookNode *book = new BookNode();
		book->bookItem = Book( bookId, bookName, bookYear );
		book->next = NULL;
		
		//setting the pointer of the last node to the new one
		retrieveBookWithIndex(sizeBookList - 1)->next = book;
		++sizeBookList;
		cout << "Book " << bookId << " has been returned" << endl;
	} 
}

int LibrarySystem::findBook( const int bookId ) {
	if ( !bookExists(bookId) ) {
		return -1;
	}
	else {
		BookNode *iter = headBook;
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
}

void LibrarySystem::deleteBook( const int bookId ) {
	if ( bookListIsEmpty() ) {
		cout << "There are no books in this LibrarySystem." << endl;
	}
	else {
		if ( !bookExists(bookId) && !searchBookInEveryStudent(bookId) ) {
			cout << "Book " << bookId << " does not exist" << endl;
		}
		else {
			//checking if a student has checked out this book
			//if it is checked, first we return the book to library
			//then delete it from the student
				StudentNode* iter = headStudent;
				while ( iter != NULL ) {
					if ( iter->studentItem.checkedBookExists(bookId) ) {
						int index = iter->studentItem.findCheckedBook(bookId);
						addBook( iter->studentItem.getCheckedBookId(index), iter->studentItem.getCheckedBookTitle(index), iter->studentItem.getCheckedBookYear(index) );
						iter->studentItem.deleteCheckedBook(bookId);
						break;
					}
					iter = iter->next;
				}
			//then we return it
			//retrieveBook(bookId)->bookItem.setChecked(false); //DNE CODE, WE DELETE IT COMPLETELY NOW
			
			//lastly, we delete it from the Library System
			BookNode* current;
			
			if ( findBook(bookId) ==  0 ) {
				current = headBook;
				headBook = headBook->next;
			}
			else {
				int index = findBook(bookId); //now "current" pointer has this node
				current = retrieveBookWithIndex(index);
				BookNode* prev = retrieveBookWithIndex(index-1);
				prev->next = current->next;
			}
			current->next = NULL;
			delete current;
			current = NULL;
			sizeBookList--;
			
			cout << "Book " << bookId << " has been deleted" << endl;
		}
	}
	
}

void LibrarySystem::deleteBookWithoutMsg( const int bookId ) {
	BookNode* current;
			
	if ( findBook(bookId) ==  0 ) {
		current = headBook;
		headBook = headBook->next;
	}
	else {
		int index = findBook(bookId); //now "current" pointer has this node
		current = retrieveBookWithIndex(index);
		BookNode* prev = retrieveBookWithIndex(index-1);
		prev->next = current->next;
	}
	current->next = NULL;
	delete current;
	current = NULL;
	sizeBookList--;
}

void LibrarySystem::removeBookList() {
	BookNode* current;
	
	//pointing the headStudent to the next node
	current = headBook;
	headBook = headBook->next;
	
	//deleting the first node in the list
	current->next = NULL;
	delete current;
	current = NULL;
	
	sizeBookList--;
}

LibrarySystem::BookNode* LibrarySystem::retrieveBook( const int bookId ) const {
	BookNode* iter = headBook;
	BookNode* nodeToReturn;

	while ( iter != NULL ) {
		if ( iter->bookItem.getBookId() == bookId ) {
			nodeToReturn = iter;
		}
		iter = iter->next;
	}
	return nodeToReturn;
}

void LibrarySystem::printListBook() {
	BookNode* iter = headBook;
	
	while ( iter != NULL ) {
		cout << iter->bookItem.getBookId() << endl;
		iter = iter->next;
	}
	cout << "sizeBookList: " << sizeBookList << endl;
}