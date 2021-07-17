#include "Student.h"
using namespace std;

Student::Student(const int id, const string firstName, const string lastName) {
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
	
	size = 0;
	head = NULL;
}

Student::~Student() {
    while (!isEmpty())
        remove(1);
}

//Student functions///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
int Student::getId() const {
    return id;
}

string Student::getFirstName() const {
    return firstName;
}

string Student::getLastName() const {
    return lastName;
}

void Student::studentAddCourse(const Course newCourse) {
    int index = getLength() + 1;

    if (!isExists(newCourse)) {
        insert(index, newCourse);
    }
}

void Student::studentDeleteCourse(const int courseId) {
    int index = findIndex(courseId);

    if (index != -1) {
        remove(index);
    }
}

void Student::deleteAllCourses() {
    while (!isEmpty())
        remove(1);
}

void Student::showCourses() const {
    if (size > 0) {
        cout << "\tCourse id" << "\tCourse name" << endl;

        for (CourseNode* temp = head; temp != NULL; temp = temp->next) {
            cout << "\t" << temp->item.getId() << setw(19) << setfill(' ') << temp->item.getTitle() << endl;
        }
    }
}

//Singly linked list functions//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Student::getLength() const {
	return size;
}

bool Student::isEmpty() const {
    return size == 0;
}

bool Student::isExists(const int courseId) const {
    bool found = false;
    
    for (CourseNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == courseId) {
            found = true;
            return found;
        }
    }

    return found;
}

bool Student::isExists(const Course course) const {
    bool found = false;
    int courseId = course.getId();
    
    for (CourseNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == courseId) {
            found = true;
            return found;
        }
    }

    return found;
}

bool Student::isExists(const int courseId, std::string& courseName) {
    bool found = false;
    courseName = "";
    
    for (CourseNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == courseId) {
            found = true;
            courseName = temp->item.getTitle();
            return found;
        }
    }

    return found;
}

void Student::insert(const int index, Course newItem) {
    int newLength = getLength() + 1;

    if (index >= 1 && index <= newLength) {
        CourseNode* newPtr = new CourseNode;
        size = newLength;
        newPtr->item = newItem;

        if (index == 1) {
            newPtr->next = head;
            head = newPtr;
        }
        else {
            CourseNode* prev = find(index-1);
            newPtr->next = prev->next;
            prev->next = newPtr;
        }
    }
}

void Student::remove(const int index) {
    CourseNode* cur;

    if (index >= 1 && index <= getLength()) {
        --size;

        if (index == 1) {
            cur = head;
            head = head->next;
        }
        else {
            CourseNode* prev = find(index-1);
            cur = prev->next;
            prev->next = cur->next;
        }
        
        cur->next = NULL;
        delete cur;
        cur = NULL;
    }
}

Student::CourseNode* Student::find(const int index) const {
    if (index < 1 || index > getLength())
        return NULL;
    else {
        CourseNode* cur = head;

        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}

int Student::findIndex(const Course item) const {
    int id = item.getId();
    int index = 1;

    for (CourseNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == id) {
            return index;
        }
        index++;
    }

    return -1;
}

int Student::findIndex(const int courseId) const {
    int index = 1;

    for (CourseNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == courseId) {
            return index;
        }
        index++;
    }

    return -1;
}