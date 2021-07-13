#include "Student.h"
using namespace std;

Student::Student(const int id, const string firstName, const string lastName) {
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
}

Student::Student(const Student& copyStudent) {
    id = copyStudent.getId();
    firstName = copyStudent.getFirstName();
    lastName = copyStudent.getLastName();
    courseList = copyStudent.getList();
}

int Student::getId() const {
    return id;
}

string Student::getFirstName() const {
    return firstName;
}

string Student::getLastName() const {
    return lastName;
}

SinglyList Student::getList() const{
    return courseList;
}

void Student::studentAddCourse(const Course newCourse) {
    int index = courseList.getLength() + 1;

    if (courseList.isExists(newCourse)) {
        cout << "Course already exists" << endl;
    }
    else {
        courseList.insert(index, newCourse);
    }
}

void Student::studentDeleteCourse(const Course course) {
    int index = courseList.findIndex(course);

    if (index != -1) {
        courseList.remove(index);
    }
}

void Student::showList() const {
    courseList.display();
}