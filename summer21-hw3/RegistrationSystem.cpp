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
        showStudentWithoutMsg(studentId);
    }
}

void RegistrationSystem::showStudentWithoutMsg(const int studentId) {
        //student information
        int index = findIndex(studentId);
        StudentNode* student = find(index);
        
        cout << student->item.getId() << setw(18) << setfill(' ') << student->item.getFirstName() << setw(12) << setfill(' ') << student->item.getLastName() << endl;
        //course information
        student->item.showCourses();
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

void RegistrationSystem::showAllStudents() {
    if (size == 0)
        cout << "There are no students in the system" << endl;
    else {
        cout << "Student id\t" << "First name\t" << "Last name\t" << endl;
        for (StudentNode* cur = head; cur != NULL; cur = cur->next) {
            showStudentWithoutMsg(cur->item.getId());
        }
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
        if ((temp->item).getId() == studentId)
            found = true;
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
            //get the address of node at the back"
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
    if (index >= 1 && index <= getLength()) {
        StudentNode* cur;

        //delete at index 1
        if (index == 1) {
            //deleting the only node
            if (size == 1) {
                //find the address of this lonely node
                cur = find(index);  
                //set the head to NULL (because there are no nodes other than cur)
                head = cur->next;
                //node is disconnected, delete it
                delete cur;
                cur = NULL;
            }
            //if there are other nodes
            else {
                //find the address of this node that is going to be deleted
                cur = find(index);
                //set the head to the next node
                head = cur->next;
                //set the next node's prev pointer to NULL
                head->prev = NULL;
                //delete this node
                delete cur;
                cur = NULL;
            }
        }
        //if the deletion is not in the first index, there is again two possibilities
        else {
            //if we are deleting the very last node
            if (index == getLength()) {
                //get the address of this node
                cur = find(index);
                //go back one node and set the next pointer of this node to NULL 
                (cur->prev)->next = NULL;
                //delete the node
                delete cur;
                cur = NULL;
            }
            else {
                //get the address of this node
                cur = find(index);
                //go back one node and set the next pointer of this node to the node at the front
                (cur->prev)->next = cur->next;
                //go front one node and set the prev pointer of this node to the node at the back
                (cur->next)->prev = cur->prev;
                //delete current node
                delete cur;
                cur = NULL;
            }
        }

        size--;
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