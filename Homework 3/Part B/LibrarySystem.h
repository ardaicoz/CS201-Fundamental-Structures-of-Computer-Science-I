#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include <string>
#include "Student.h"
#include "Book.h"


class LibrarySystem {
public:
	LibrarySystem();
	~LibrarySystem();
	
	void addBook( const int bookId, const std::string bookName, const int bookYear );
	void addBookWithoutMsg( const int bookId, const std::string bookName, const int bookYear );
	void deleteBook( const int bookId );
	void deleteBookWithoutMsg( const int bookId );
	
	void addStudent( const int studentId, const std::string studentName );
	void deleteStudent( const int studentId );
	
	void checkoutBook(const int bookId, const int studentId );
	void returnBook( const int bookId );
	
	void showAllBooks() const;
	void showBook(const int bookId) const;
	void showStudent( const int studentId ) const;
	
	//extra functions for student list
	bool studentExists( const int studentId ) const;
	bool studentListIsEmpty();
	int studentListGetLength(); 
	int findStudent( const int studentId ); //returns the index of that student in the list
	void printList(); //TEST
	bool searchBookInEveryStudent( const int bookId ) const;
	
	//extra functions for book list
	bool bookListIsEmpty();
	bool bookExists( const int bookId ) const;
	int findBook( const int bookId );
	void printListBook(); //TEST

private:
	//private members for students
	struct StudentNode {
		Student studentItem;
		StudentNode *next;
	};
	int sizeStudentList;
	StudentNode *headStudent;
	
	StudentNode* retrieveStudent( const int studentId ) const; //returns a StudentNode pointer for that student (using id of the student)
	StudentNode* retrieveStudentWithIndex( const int index );  //returns a StudentNode pointer for that student (by specifying the index location)
	void removeStudentList(); //exclusive for destructor
	
	//private members for books
	struct BookNode {
		Book bookItem;
		BookNode *next;
	};
	int sizeBookList;
	BookNode *headBook;
	
	BookNode* retrieveBook( const int bookId ) const;
	BookNode* retrieveBookWithIndex( const int index );  //returns a BookNode pointer for that student (by specifying the index location)
	void removeBookList(); //exclusive for destructor
};

#endif // LIBRARYSYSTEM_H
