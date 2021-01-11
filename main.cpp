#include <iostream>
#include "DynamicArray.h"
#include "HashTable.h"
#include "AVLTree.h"
#include "CoursesManager.h"
using std::cout;
using std::endl;

int main() {

    CoursesManager cm;
    int course_num;
    int class_num;
    int time_viewed;
    cm.AddCourse(234218);
    cm.AddCourse(234247);
    cm.AddClass(234218, &class_num);
    cm.AddClass(234218, &class_num);
    cm.AddClass(234247, &class_num);
    cm.AddClass(234123, &class_num);
    cm.WatchClass(234218,1,10);
    cm.TimeViewed(234218,1,&time_viewed);
    cm.WatchClass(234247,0,20);
    cm.TimeViewed(234247,0,&time_viewed);
    cm.GetIthWatchedClass(0,&course_num,&class_num);
    cm.GetIthWatchedClass(1,&course_num,&class_num);
    cout << "Course: " << course_num << " Class: " << class_num << endl;
    cm.GetIthWatchedClass(3,&course_num,&class_num);
    cm.GetIthWatchedClass(2,&course_num,&class_num);

    /*DynamicArray<int> arr;
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(11);
    arr.push_back(3);
    arr.push_back(23);
    for (int i = 0; i < arr.quantity(); ++i) {
        cout << arr[i] <<endl;
    }
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    cout << endl;*/
//    AVLTree<int> tree;
//    for (int i = 1; i < 2000000; i= i*6) {
//        //int k = (i % 15) + i - 14 * 3;
//        tree.insert_value(i);
//    }
//
//    cout << tree.getIthElement(tree.get_root(), 5) << endl;

//    for (int i = 0; i < 1999; ++i) {
//        if(i%7)
//            tree.delete_value(tree.get_root(), i);
//    }
//    tree.insert_value(1);
//    tree.in_order(tree.get_root());

//    HashTable<int> hash;
//    hash.insert(8);
//    hash.insert(4);
//    hash.insert(6);
//    hash.insert(7);
//    hash.insert(34);
//    hash.insert(44);
//    hash.insert(234);
//    hash.insert(34345);
////    hash.insert(34423);
////    hash.insert(7);
//    cout << hash << endl;
//    hash.remove(4);
//    hash.remove(4654);
//    hash.remove(234);
//    hash.remove(234);
//    hash.remove(34423);
//    hash.remove(421);
//    hash.remove(42);
//    hash.remove(8);
//    hash.remove(6);
//    hash.remove(7);
////    hash.remove(34);
//    hash.remove(44);
//    hash.remove(234);
//    hash.remove(34345);
//    hash.remove(34423);
//    cout << hash << endl;

    return 0;
}