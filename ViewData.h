#ifndef HW2_VIEW_DATA_H
#define HW2_VIEW_DATA_H

class ViewData {
    int course;
    int lecture;
    int timeViewed;
public:
    explicit ViewData(int course = 0 , int lecture = 0, int timeViewed = 0) : course(course), lecture(lecture), timeViewed(timeViewed){}

    void setTimeViewed(int new_timeViewed) { timeViewed = new_timeViewed; }
    void setLecture(int new_lecture)       { lecture = new_lecture; }
    void setCourse(int new_course)         { course = new_course; }

    int getTimeViewed() const { return timeViewed; }
    int getLecture() const    { return lecture; }
    int getCourse() const     { return course; }

    bool operator<(const ViewData& data) const {
        if(timeViewed < data.timeViewed)
            return true;
        else if(timeViewed > data.timeViewed)
            return false;
        else if (course > data.course)
            return true;
        else if(course < data.course)
            return false;
        else if(lecture > data.lecture)
            return true;
        else if(lecture < data.lecture)
            return false;
        return false;
    }
    bool operator>(const ViewData& data) const {
        return (data < *this);
    }
    bool operator==(const ViewData& data) const {
        return (timeViewed == data.timeViewed && course == data.course && lecture == data.lecture);
    }

    friend std::ostream& operator<<(std::ostream& os, const ViewData& data) {
        os << "Course ID : " << data.course << ", Lecture ID : " << data.lecture << ", Watch time : " << data.timeViewed << std::endl;
        return os;
    }
};

#endif //HW2_VIEW_DATA_H