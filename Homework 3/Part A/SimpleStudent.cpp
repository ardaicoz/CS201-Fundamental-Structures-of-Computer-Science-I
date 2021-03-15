#include "SimpleStudent.h"
#include <string>
#include <iostream>
using namespace std;

Student::Student( const string stuName, const int stuId ) {
	studentName = stuName;
	
	if ( stuId > 0 )
		studentId = stuId;
}

Student::~Student() {
	
}

string Student::getName() {
	return studentName;
}

int Student::getId() {
	return studentId;
}



