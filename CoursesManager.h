#ifndef HW2_COURSESMANAGER_H
#define HW2_COURSESMANAGER_H

#include "library2.h"
#include "AVLTree.h"
#include "Course.h"
#include "ViewData.h"
#include "HashTable.h"
#include <memory>

class CoursesManager {
public:
    ~CoursesManager() = default;
    HashTable<Course> courses_hash;
    AVLTree<ViewData> watched_lecture_tree;

    StatusType AddCourse (int courseID);

    StatusType RemoveCourse(int courseID);

    StatusType AddClass(int courseID, int* classID);

    StatusType WatchClass(int courseID, int classID, int time);

    StatusType TimeViewed(int courseID, int classID, int *timeViewed);

    StatusType GetIthWatchedClass(int i, int* courseID, int* classID);

};

#endif //HW2_COURSESMANAGER_H