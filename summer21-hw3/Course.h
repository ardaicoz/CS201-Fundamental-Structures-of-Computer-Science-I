#ifndef __COURSE_H
#define __COURSE_H
#include <iostream>

class Course {
public:
    Course(const int id = 0, const std::string title = "");
    Course(const Course& copyCourse);

    int getId() const;
    std::string getTitle() const;

    void setId(const int id);
    void setTitle(const std::string title);

private:
    int id;
    std::string title;
};

#endif