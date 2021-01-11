#include "CoursesManager.h"

StatusType CoursesManager::AddCourse(int courseID) {
    Course new_course(courseID);
    if(courses_hash.insert(new_course) == false)
        return FAILURE;

    return SUCCESS;
}

StatusType CoursesManager::RemoveCourse(int courseID) {

    Course temp(courseID);
    Course* course_to_remove = courses_hash.search(temp);
    if(course_to_remove == nullptr)
        return FAILURE;
    for(int i = 0; i < course_to_remove->lectures.size(); i++) {
        ViewData temp_lecture(courseID, i, course_to_remove->lectures[i]);
        watched_lecture_tree.delete_value(temp_lecture)
    }
    return SUCCESS;
}

StatusType CoursesManager::WatchClass(int courseID, int classID, int time) {

    AVLNode<Course>* temp_node = course_tree.find_value(course_tree.get_root(), Course(courseID));

    // no class with this id in course.
    if(temp_node != nullptr && (classID + 1 > temp_node->data.lectures.size()))
        return INVALID_INPUT;
    // no course with this id.
    if(temp_node == nullptr)
        return FAILURE;

    int old_time_viewed = temp_node->data.lectures[classID].timed_watched;
    // remove old lecture from watched tree and insert the new one (with the updated time).
    if(old_time_viewed > 0) {
        if(strongest_lecture->data == ViewData(courseID,classID,old_time_viewed))
            strongest_lecture = nullptr;
        watched_lecture_tree.delete_value(watched_lecture_tree.get_root(),ViewData(courseID, classID, old_time_viewed));

    }
    watched_lecture_tree.insert_value(ViewData(courseID, classID, old_time_viewed + time));
    temp_node->data.lectures[classID].add_time(time);

    ViewData recent_lecture(courseID, classID, old_time_viewed + time);

    if(strongest_lecture == nullptr)
        strongest_lecture = watched_lecture_tree.find_value(watched_lecture_tree.get_root(), recent_lecture);
    else if(strongest_lecture->data < recent_lecture)
        strongest_lecture = watched_lecture_tree.find_value(watched_lecture_tree.get_root(), recent_lecture);

    // remove class from empty list and set pointer to that list to null (if it is not null already).
    if(temp_node->data.pointers_to_empty_lectures[classID] != nullptr)
        temp_node->data.empty_lecture.removeNode(temp_node->data.pointers_to_empty_lectures[classID]);
    temp_node->data.pointers_to_empty_lectures[classID] = nullptr;

    // if no empty lectures left in course, remove it from empty_tree.
    if(temp_node->data.empty_lecture.head == nullptr) {
        empty_courses_tree.delete_value(empty_courses_tree.get_root(), EmptyCourse(courseID, temp_node));
        strongest_empty_course = empty_courses_tree.find_max(empty_courses_tree.get_root());
    }
    return SUCCESS;
}

StatusType CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed) {
    Course temp_course(courseID);
    AVLNode<Course>* temp = course_tree.find_value(course_tree.get_root(), temp_course);
    // no course with such id.
    if(temp != nullptr && classID + 1 > temp->data.lectures.size())
        return INVALID_INPUT;

    // no class with such id.
    if(temp == nullptr)
        return FAILURE;

    *timeViewed = temp->data.lectures[classID].timed_watched;
    return SUCCESS;
}

StatusType CoursesManager::AddClass(int courseID, int *classID) {
    return INVALID_INPUT;
}

StatusType CoursesManager::GetIthWatchedClass(int i, int* courseID, int* classID) {

    AVLNode<ViewData>* temp_most_viewed = strongest_lecture;

    // there aren't enough lectures in the system!
    if(numOfClasses > lectures_counter)
        return FAILURE;

    int remained = numOfClasses;
    int counted = 0;
    // start printing from the watched lecture tree.
    while(temp_most_viewed != nullptr && remained > 0) {
        courses[counted] = temp_most_viewed->data.getCourse();
        classes[counted] = temp_most_viewed->data.getLecture();
        counted++;
        remained--;
        watched_lecture_tree.reverse_in_order(temp_most_viewed->get_left(), &remained, &counted, courses, classes);
        temp_most_viewed = temp_most_viewed->get_parent();
    }

    // printed enough lectures.
    if (counted >= numOfClasses) {
        return SUCCESS;
    }

    // start printing from the empty printing tree.
    AVLNode<EmptyCourse>* temp_strongest_empty_course = strongest_empty_course;
    while(temp_strongest_empty_course != nullptr && remained > 0) {
        Node<int>* head_list = temp_strongest_empty_course->data.getCoursePtr()->data.empty_lecture.head;
        while (head_list && remained > 0){
            courses[counted] = temp_strongest_empty_course->data.getCourseID();
            classes[counted] = head_list->getData();
            head_list = head_list->getNext();
            counted++;
            remained--;
        }
        empty_courses_tree.reverse_in_order_empty(temp_strongest_empty_course->get_left(), &remained, &counted, courses, classes);
        temp_strongest_empty_course = temp_strongest_empty_course->get_parent();
    }
    return SUCCESS;
}