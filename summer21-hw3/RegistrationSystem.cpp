#include "RegistrationSystem.h"
using namespace std;

RegistrationSystem::RegistrationSystem() : size(0), head(NULL) {}

RegistrationSystem::~RegistrationSystem() {
    while ( !isEmpty() )
        remove(1);
}

//Registration System functions///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RegistrationSystem::addStudent(const int studentId, const std::string firstName, const std::string lastName) {
    if (isExists(studentId))
        cout << "Student " << studentId << " already exists" << endl;
    else {
        if (getLength() == 0) {
            //insert function accepts a Student object as a parameter so creating it first then inserting it to the list
            insert( 1, Student(studentId, firstName, lastName) );
        }
        else {
            //whereToInsert function finds the proper place in order this list to be sorted
            insert( whereToInsert(studentId), Student(studentId, firstName, lastName) );
        }
        cout << "Student " << studentId << " has been added" << endl;
    }
}

void RegistrationSystem::deleteStudent(const int studentId) {
    if (!isExists(studentId))
        cout << "Student " << studentId << " does not exist" << endl;
    else {
        //remove function already deletes all courses for that student
        int index = findIndex(studentId);
        StudentNode* temp = find(index);
        
        temp->item.deleteAllCourses();
        remove(index);
        
        cout << "Student " << studentId << " has been deleted" << endl;
    }
}

void RegistrationSystem::addCourse(const int studentId, const int courseId, const string courseName) {
    if (!isExists(studentId))
        cout << "Student " << studentId << " does not exist" << endl;
    else {
        int index = findIndex(studentId);
        StudentNode* student = find(index);

        if (student->item.isExists(courseId))
            cout << "Student " << studentId << " is already enrolled in course " << courseId << endl;
        else {
            student->item.studentAddCourse( Course(courseId, courseName) );
            cout << "Course " << courseId << " has been added to student " << studentId << endl;
        }
    }
}

void RegistrationSystem::withdrawCourse(const int studentId, const int courseId) {
    if (!isExists(studentId))
        cout << "Student " << studentId << " does not exist" << endl;
    else {
        int index = findIndex(studentId);
        StudentNode* student = find(index);

        if (student->item.isExists(courseId))
            cout << "Student " << studentId << " is not enrolled in course " << courseId << endl;
        else {
            student->item.studentDeleteCourse(courseId);
            cout << "Student " << studentId << " has been withdrawn from course " << courseId << endl;
        }
    }
}

void RegistrationSystem::cancelCourse(const int courseId) {
    for (StudentNode* cur = head; cur != NULL; cur = cur->next) {
        if (cur->item.isExists(courseId)) {
            cur->item.studentDeleteCourse(courseId);
        }
    }
    cout << "Course " << courseId << " has been cancelled" << endl; 
}

void RegistrationSystem::showStudent(const int studentId) {
    if (!isExists(studentId))
        cout << "Student " << studentId << " does not exist" << endl;
    else {
        cout << "Student id\t" << "First name\t" << "Last name\t" << endl;

        //student information
        int index = findIndex(studentId);
        StudentNode* student = find(index);
        
        cout << student->item.getId() << setw(18) << setfill(' ') << student->item.getFirstName() << setw(12) << setfill(' ') << student->item.getLastName() << endl;
        //course information
        student->item.showCourses();
    }
}

void RegistrationSystem::showCourse(const int courseId) {
    //search if this course exists
    bool found = false;
    string courseName = "";

    for (StudentNode* cur = head; cur != NULL; cur = cur->next) {
        if ( cur->item.isExists(courseId, courseName) ) {
            found = true;
        }
    }

    if (!found)
        cout << "Course " << courseId << " does not exist" << endl;
    else {
        cout << "Course id\t" << "Course name" << endl;
        cout << courseId << setw(19) << setfill(' ') << courseName << endl;
        cout << "\tStudent id" << "\tFirst name" << "\tLast name" << endl;

        //print students
        for (StudentNode* cur = head; cur != NULL; cur = cur->next) {
            if ( cur->item.isExists(courseId, courseName) ) {
                cout << "\t" << cur->item.getId() << setw(19) << setfill(' ') << cur->item.getFirstName() << setw(19) << setfill(' ') << cur->item.getLastName() << endl; 
            }
        }
    }
}

void RegistrationSystem::showList() const {
    if (size == 0) {
        cout << "SinglyList is empty" << endl;
    }
    else {
        cout << "Students: [";
        for (StudentNode* temp = head; temp != NULL; temp = temp->next) {
            cout << (temp->item).getId() << " " << (temp->item).getFirstName() << (temp->item).getLastName() <<  " - ";
        }
        cout << "]" << endl;
    }
}

//Doubly linked list functions/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RegistrationSystem::isEmpty() const {
    return size == 0;
}

int RegistrationSystem::getLength() const {
    return size;
}

bool RegistrationSystem::isExists(const int studentId) const {
    bool found = false;
    
    for (StudentNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == studentId) {
            found = true;
            return found;
        }
    }

    return found;
}

bool RegistrationSystem::isExists(const Student student) const {
    bool found = false;
    int studentId = student.getId();
    
    for (StudentNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == studentId) {
            found = true;
            return found;
        }
    }

    return found;
}

void RegistrationSystem::insert(const int index, Student newItem) {
    int newLength = getLength() + 1;

    if (index >= 1 && index <= newLength) {
        //created a new node
        StudentNode* newPtr = new StudentNode;
        //set the new size and put this item to this node
        size = newLength;
        newPtr->item = newItem;

        if (index == 1) {
            //next pointer of this node will point to previously first node
            newPtr->next = head;
            //prev pointer will be NULL becuase index is 1
            newPtr->prev = NULL;
            //head pointer now point to this new node
            head = newPtr;
        }
        else {
            //get the address of node at the back
            StudentNode* prevNode = find(index-1);
            //new node's next pointer will now point to node that was previously in front of prev node
            newPtr->next = prevNode->next;
            //prev node's next pointer will now point to this new node (new node is fitted between these two nodes)
            prevNode->next = newPtr;
            //new node's prev pointer will now point to node that was previously in this index 
            newPtr->prev = prevNode;

            //if addition happens between two nodes (if index equals to newLength, addition happens in the very end), 
            //set the front node's prev pointer to new node
            if (index != newLength)
                newPtr->next->prev = newPtr;
        }
    }
}

void RegistrationSystem::remove(const int index) {
    StudentNode* cur;

    if (index >= 1 && index <= getLength()) {
        --size;

        if (index == 1) {
            //temp pointer of cur now points to the first node (which is also pointed by "head")
            cur = head;
            //head pointer skips this node and points to the next node (this skipped node will be deleted)
            //cur pointer still points to the lonely node
            head = head->next;
            //disconnecting the next node from skipped node
            head->prev = NULL;
        }
        else {
            //get the address of the node at the back
            StudentNode* prev = find(index-1);
            //cur pointer now points to the node that is in front of prev node
            cur = prev->next;
            //prev node's next pointer skips the node in front of it and point to the next node
            prev->next = cur->next;
            //connecting the next node to prev node
            cur->next->prev = prev;
        }
        
        //in every case, cur pointer points to the node to be deleted 
        //disconnecting this node from actual list
        cur->next = NULL;
        cur->prev = NULL;
        //deleting the node
        delete cur;
        cur = NULL;
    }
}

RegistrationSystem::StudentNode* RegistrationSystem::find(const int index) const {
    if (index < 1 || index > getLength())
        return NULL;
    else {
        StudentNode* cur = head;

        for (int skip = 1; skip < index; ++skip)
            cur = cur->next;
        return cur;
    }
}

int RegistrationSystem::findIndex(const int studentId) const {
    int index = 1;

    for (StudentNode* temp = head; temp != NULL; temp = temp->next) {
        if ((temp->item).getId() == studentId) {
            return index;
        }
        index++;
    }

    return -1;
}

int RegistrationSystem::whereToInsert(const int id) const {
    if (size >= 1) {
        int index = 1;

        for (StudentNode* temp = head; temp != NULL; temp = temp->next) {
            if (temp->item.getId() >= id) {
               return index; 
            }
            index++;
        }

        return index;
    }

    return -1;
}