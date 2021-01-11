#include "CoursesManager.h"

StatusType CoursesManager::AddCourse(int courseID) {
    Course new_course(courseID);
    if(courses_hash.insert(new_course) == false)
        return FAILURE;

    return SUCCESS;
}

StatusType CoursesManager::RemoveCourse(int courseID) {

    Course* course_to_remove = courses_hash.search(Course(courseID));
    if(course_to_remove == nullptr)
        return FAILURE;
    for(int i = 0; i < course_to_remove->lectures.size(); i++) {
        ViewData temp_lecture(courseID, i, course_to_remove->lectures[i]);
        watched_lecture_tree.delete_value(watched_lecture_tree.get_root(), temp_lecture);
    }
    courses_hash.remove(*course_to_remove);
    return SUCCESS;
}

StatusType CoursesManager::WatchClass(int courseID, int classID, int time) {

    Course* temp_course = courses_hash.search(Course(courseID));

    // no class with this id in course.
    if(temp_course != nullptr && (classID + 1 > temp_course->lectures.size()))
        return INVALID_INPUT;
    // no course with this id.
    if(temp_course == nullptr)
        return FAILURE;

    int old_time_viewed = temp_course->lectures[classID];
    // remove old lecture from watched tree and insert the new one (with the updated time).
    if(old_time_viewed > 0)
        watched_lecture_tree.delete_value(watched_lecture_tree.get_root(), ViewData(courseID, classID, old_time_viewed));
    watched_lecture_tree.insert_value(ViewData(courseID, classID, old_time_viewed + time));
    temp_course->lectures[classID] = old_time_viewed + time;

    return SUCCESS;
}

StatusType CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed) {

    Course* temp_course = courses_hash.search(Course(courseID));
    // no class with such id.
    if(temp_course != nullptr && classID + 1 > temp_course->lectures.size())
        return INVALID_INPUT;

    // no course with such id.
    if(temp_course == nullptr)
        return FAILURE;

    *timeViewed = temp_course->lectures[classID];
    return SUCCESS;
}

StatusType CoursesManager::AddClass(int courseID, int *classID) {
    Course* temp_course = courses_hash.search(Course(courseID));
    // no course with such id.
    if(temp_course == nullptr)
        return FAILURE;

    temp_course->lectures.push_back(0);
    *classID = temp_course->lectures.size() - 1;
    return SUCCESS;
}

StatusType CoursesManager::GetIthWatchedClass(int i, int* courseID, int* classID) {

    // there aren't enough watched lectures in the system!
    if(watched_lecture_tree.get_nodes_counter() < i)
        return FAILURE;
    AVLNode<ViewData>* temp = watched_lecture_tree.get_root();
    while(temp) {
        if(watched_lecture_tree.calc_rank(watched_lecture_tree.get_root(), temp->data) == i) {
            // how to implement??
        }
    }
    return SUCCESS;
}