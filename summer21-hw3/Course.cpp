#include "Course.h"
using namespace std;

Course::Course(const int id, const string title) {
    this->id = id;
    this->title = title;
}

Course::Course(const Course& copyCourse) {
    id = copyCourse.getId();
    title = copyCourse.getTitle();
}

int Course::getId() const {
    return id;
}
    
string Course::getTitle() const {
    return title;
}

void Course::setId(const int id) {
    this->id = id;
}

void Course::setTitle(const string title) {
    this->title = title;
}