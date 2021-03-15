#ifndef BOOK_H
#define BOOK_H
#include <string>

class Book {
public:
	Book( const int bookId = 0, const std::string bookTitle = "", const int bookYear = 0 );
	~Book();
	
	int getBookId();
	std::string getBookTitle();
	int getBookYear();
	bool isChecked();
	void setChecked( bool checked );

private:
	int bookId;
	std::string bookTitle;
	int bookYear;
	bool checked;
};

#endif // BOOK_H
