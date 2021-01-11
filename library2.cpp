#include "library2.h"
#include "CoursesManager.h"

void *Init() {
    CoursesManager *DS = new CoursesManager ();
    return (void*)DS;
}

StatusType AddCourse(void *DS, int courseID) {

    if(courseID <= 0 || DS == nullptr)
        return INVALID_INPUT;
    try {
        StatusType status(((CoursesManager *)DS)->AddCourse(courseID));
        return status;
    }
    catch (const std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType AddClass(void* DS, int courseID, int* classID) {
    if(courseID <= 0 || DS == nullptr)
        return INVALID_INPUT;
    try {
        StatusType status(((CoursesManager *)DS)->AddClass(courseID, classID));
        return status;
    }
    catch (const std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveCourse(void *DS, int courseID) {

    if(courseID <= 0 || DS == nullptr)
        return INVALID_INPUT;
    try {
        StatusType status(((CoursesManager *)DS)->RemoveCourse(courseID));
        return status;
    }
    catch (const std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed) {

    if(classID < 0 || courseID <= 0 || DS == nullptr)
        return INVALID_INPUT;
    try {
        StatusType status(((CoursesManager *)DS)->TimeViewed(courseID, classID, timeViewed));
        return status;
    }
    catch (const std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType WatchClass(void *DS, int courseID, int classID, int time) {

    if(time <= 0 || classID < 0 || courseID <= 0 || DS == nullptr)
        return INVALID_INPUT;
    try {
        StatusType status(((CoursesManager *)DS)->WatchClass(courseID, classID, time));
        return status;
    }
    catch (const std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

StatusType GetIthWatchedClass(void *DS, int i, int *courseID, int *classID) {

    if(i <= 0 || DS == nullptr)
        return INVALID_INPUT;
    try {
        StatusType status(((CoursesManager *)DS)->GetIthWatchedClass(i, courseID, classID));
        return status;
    }
    catch (const std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS) {

    delete static_cast<CoursesManager*>(*DS);
    *DS = nullptr;
}