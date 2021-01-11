#include <iostream>
#include "DynamicArray.h"
#include "HashTable.h"
#include "AVLTree.h"
using std::cout;
using std::endl;

int main() {
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
    AVLTree<int> tree;
    for (int i = 0; i < 2000; ++i) {
        //int k = (i % 15) + i - 14 * 3;
        tree.insert_value(i);
    }

    for (int i = 0; i < 1999; ++i) {
        tree.delete_value(tree.get_root(), i);
    }
    tree.insert_value(1);
    tree.in_order(tree.get_root());
    return 0;
}