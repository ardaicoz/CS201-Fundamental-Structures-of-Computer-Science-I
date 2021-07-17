#ifndef __REGISTRATIONSYSTEM_H
#define __REGISTRATIONSYSTEM_H
#include <iostream>
#include <iomanip>
#include "Student.h"

class RegistrationSystem {
public :
    RegistrationSystem();
    ~RegistrationSystem();
    
    void addStudent(const int studentId, const std::string firstName, const std::string lastName);
    void deleteStudent(const int studentId);
    
    void addCourse(const int studentId, const int courseId, const std::string courseName);
    void withdrawCourse(const int studentId, const int courseId);
    void cancelCourse(const int courseId);
    
    void showStudent(const int studentId);
    void showCourse(const int courseId);
    void showAllStudents();

    void showList() const;
    
private:
    //Declaring doubly linked list
    struct StudentNode {
        Student item;
        StudentNode* next;
        StudentNode* prev;
    };
    int size;
    StudentNode* head;

    //Doubly linked list functions
    bool isEmpty() const;
    int getLength() const;

    bool isExists(const int studentId) const;
	bool isExists(const Student student) const;
    
    void insert(const int index, Student newItem);
    void remove(const int index);

    StudentNode* find(const int index) const;
    int findIndex(const int studentId) const;

    int whereToInsert(const int id) const;

};  

#endif