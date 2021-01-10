#include <iostream>
#include "DynamicArray.h"


using std::cout;
using std::endl;

int main() {
    DynamicArray<int> arr;
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
    return 0;
}
