#ifndef __STUDENT_H
#define __STUDENT_H
#include <iostream>
#include "SinglyList.h"

class Student {
public:
    Student(const int id = 0, const std::string firstName = "", const std::string lastName = "");
    Student(const Student& copyStudent);

    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    SinglyList getList() const;

    void studentAddCourse(const Course course);
    void studentDeleteCourse(const Course course);
    void showList() const;


private:
    int id;
    std::string firstName;
    std::string lastName;
    
    SinglyList courseList;
};

#endif