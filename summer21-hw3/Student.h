#ifndef __STUDENT_H
#define __STUDENT_H
#include <iostream>
#include <iomanip>
#include "Course.h"

class Student {
public:
    Student(const int id = 0, const std::string firstName = "", const std::string lastName = "");
    ~Student();
    Student& operator=(const Student&);

    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;

    void studentAddCourse(const Course course); //uses insert function
    void studentDeleteCourse(const int courseId); //uses remove function   
    void deleteAllCourses(); //same with destructor

    void showCourses() const;

    //Singly linked list function
    bool isExists(const int courseId) const;
    bool isExists(const int courseId, std::string& courseName);

private:
	//Student data members
	int id;
    std::string firstName;
    std::string lastName;
	
	//Singly linked list to store courses
    struct CourseNode {
        Course item;
        CourseNode* next;
    };
	int size;
	CourseNode* head;
	
	//Singly linked list functions
    int getLength() const;
    bool isEmpty() const;
    
    void insert(const int index, Course newItem);
    void remove(const int index);

    CourseNode* find(const int index) const;
    int findIndex(const int courseId) const;
    
};

#endif