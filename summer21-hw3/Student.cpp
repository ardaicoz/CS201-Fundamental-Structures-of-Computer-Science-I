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
        cout << "Student " << id << " is already enrolled in course " << newCourse.getId() << endl;
    }
    else {
        courseList.insert(index, newCourse);
        cout << "Course " << newCourse.getId() << " has been added to student " << id << endl;
    }
}

void Student::studentDeleteCourse(const Course course) {
    int index = courseList.findIndex(course);

    if (index != -1) {
        courseList.remove(index);
        cout << "Student " << id << " has been withdrawn from course " << course.getId() << endl;
    }
    else {
        cout << "Student " << id << " is not enrolled in course " << course.getId() << endl;
    }
}

void Student::showList() const {
    courseList.display();
}