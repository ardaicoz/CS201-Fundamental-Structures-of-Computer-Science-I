#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include <string>
#include "SimpleStudent.h"


class LibrarySystem {
public:
	LibrarySystem();
	~LibrarySystem();
	
	void addStudent( const int studentId, const std::string studentName );
	void deleteStudent( const int studentId );
	void showStudent( const int studentId ) const;
	
	//extra functions for student list
	bool studentExists( const int studentId ) const;
	bool studentListIsEmpty();
	int studentListGetLength(); 
	int findStudent( const int studentId ); //returns the index of that student in the list
	void printList(); //TEST
	

private:
	struct StudentNode {
		Student studentItem;
		StudentNode *next;
	};
	int size;
	StudentNode *head;
	
	StudentNode* retrieveStudent( const int studentId ) const; //returns a StudentNode pointer for that student (using id of the student)
	StudentNode* retrieveStudentWithIndex( const int index );  //returns a StudentNode pointer for that student (by specifying the index location)
	void removeStudentList(); //exclusive for destructor
};

#endif // LIBRARYSYSTEM_H

