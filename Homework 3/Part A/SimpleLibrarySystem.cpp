#include "SimpleLibrarySystem.h"
#include <iostream>
using namespace std;

LibrarySystem::LibrarySystem() {
	size = 0;
	head = NULL;
}

LibrarySystem::~LibrarySystem() {
	while ( !studentListIsEmpty() ) {
		removeStudentList();
	}
}

void LibrarySystem::addStudent( const int studentId, const string studentName ) {
	if ( studentListIsEmpty() ) {
		//creating the node and initializing it
		StudentNode *student = new StudentNode();
		student->studentItem = Student( studentName, studentId );
		student->next = NULL;
		
		//setting head pointer to the new node
		head = student;
		size++;
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
			retrieveStudentWithIndex(size-1)->next = student;
			++size;
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
			StudentNode* current;
			
			if ( findStudent(studentId) == size - 1 ) {
				current = head;
				head = head->next;
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
			size--;
			cout << "Student " << studentId << " has been deleted" << endl;
		}
	}
}

bool LibrarySystem::studentExists( const int studentId ) const {
	StudentNode *iter = head;
	
	while ( iter != NULL ) {
		if ( iter->studentItem.getId() == studentId ) {
			return true;
		}
		iter = iter->next;
	}
	return false;
}

bool LibrarySystem::studentListIsEmpty() {
	return (size == 0);
}

int LibrarySystem::studentListGetLength() {
	return size;
}

int LibrarySystem::findStudent( const int studentId ) {
	if ( !studentExists(studentId) ) {
		return -1;
	}
	else {
		StudentNode *iter = head;
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
	StudentNode* iter = head;
	
	while ( iter != NULL ) {
		cout << iter->studentItem.getId() << endl;
		iter = iter->next;
	}
	cout << "size: " << size << endl;
}

LibrarySystem::StudentNode* LibrarySystem::retrieveStudent( const int studentId ) const {
	StudentNode* iter = head;
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
	StudentNode* nodeToReturn = head;
	
	for ( int i = 0; i < index; i++ ) { 
		nodeToReturn = nodeToReturn->next;
	}
	return nodeToReturn;
}

void LibrarySystem::removeStudentList() {
	StudentNode* current;
	
	//pointing the head to the next node
	current = head;
	head = head->next;
	
	//deleting the first node in the list
	current->next = NULL;
	delete current;
	current = NULL;
	
	size--;
}

