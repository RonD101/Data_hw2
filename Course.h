#ifndef HW2_COURSE_H
#define HW2_COURSE_H

#include "DynamicArray.h"

class Course {
public:
    explicit Course(int id) : id(id) {}

    int id;
    DynamicArray<int> lectures;

    // Courses are ordered by id only.
    bool operator==(const Course &other) const {
        return (id == other.id);
    }
    bool operator<(const Course &other) const {
        return (id < other.id);
    }
    bool operator>(const Course &other) const {
        return (id > other.id);
    }

    int operator%(int module) const {
        return id % module;
    }

    friend std::ostream& operator<<(std::ostream& os, const Course& c){
        os << "Course ID : " << c.id << std::endl;
        for(int i = 0; i < c.lectures.size(); i++)
            os << c.lectures[i] << std::endl;
        return os;
    }
};

#endif //HW2_COURSE_H