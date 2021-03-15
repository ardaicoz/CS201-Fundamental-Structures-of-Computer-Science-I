#ifndef STUDENT_H
#define STUDENT_H
#include <string>

class Student {
public:
	Student( const std::string stuName = "", const int stuId = 0 ); //default constructor and normal constructor combined
	~Student();
	
	std::string getName();
	int getId();
	
private:
	std::string studentName;
	int studentId;
};

#endif // STUDENT_H
