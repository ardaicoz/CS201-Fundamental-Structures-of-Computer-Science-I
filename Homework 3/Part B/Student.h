#ifndef STUDENT_H
#define STUDENT_H
#include "Book.h"
#include <string>

class Student {
public:
	Student( const std::string stuName = "", const int stuId = 0 ); //default constructor and normal constructor combined
	~Student();
	
	std::string getName();
	int getId();
	int getListSize();
	void deleteCheckedBook( const int bookId );
	int findCheckedBook( const int bookId );
	void addCheckedBook( const int bookId, const std::string bookName, const int bookYear );
	bool checkedBookExists( const int bookId ) const;
	
	//public functions for book info
	int getCheckedBookId( const int index );
	std::string getCheckedBookTitle( const int index );
	int getCheckedBookYear( const int index );
	
private:
	std::string studentName;
	int studentId;
	
	struct CheckedBook {
		Book bookItem;
		CheckedBook *next;
	};
	int size;
	CheckedBook *head;
	
	CheckedBook* retrieveCheckedBookWithIndex( const int index );
	void removeCheckedBookList();
};

#endif // STUDENT_H