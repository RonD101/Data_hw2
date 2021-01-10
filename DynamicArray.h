//
// Created by Ron Dahan on 20/06/2020.
//

#ifndef HW2_DYNAMICARRAY_H
#define HW2_DYNAMICARRAY_H
#define EXPAND_FACTOR 2

#include <iostream>
#include <string>

/**
* Template Dynamic Array
*
* Implements a generic typed array.
* with an Exception class of BadAccess
*
* The following functions are available:
*   the big three - constructor , destructor and copy constructor.
*   size		- Return the size of the array.
*
* The following operators are available:
*   operator=      - Assignment of one matrix to the other
*   operator[]      - Return reference to value
*/
    template<class T>
    class DynamicArray {
        T *data;
        int length;
        int current;
    public:
        class BadAccess;

/**
*	Constructor: create a new Template Dynamic Array
*
* @param
* size - The Initial size of the Array(optional)
* @return
* 	The new Array
* @assumption
*   There is a default constructor for class T.
*/
        explicit DynamicArray(int size = 2);

/**
*	Copy Constructor: create a copy Array
*
* @param
* DynamicArray - The template DynamicA rray which we copy the values from.
* @return
* 	The copied Array
* @assumption
*   There is a default constructor for class T.
*   There is a '=' operator implement for class T.
*/
        DynamicArray(const DynamicArray<T> &a);

/**
*    Destructor: Destroy the Template Dynamic Array when her 'life' end.
*
* @return
* 	No Return Value.
* @assumption
*   There is a default destructor for class T.
*/
        ~DynamicArray();

/**
*	operator=: assign template Dynamic  Array
*
* @param
* DynamicArray - The template DynamicA rray which we copy the values from.
* @return
* 	The assigned array
* @assumption
*   There is a default constructor for class T.
*   There is a default destructor for class T.
*   There is a '=' operator implement for class T.
*/
        DynamicArray &operator=(const DynamicArray<T> &a);

/**
*	size: Returns the amount of element in array.
*
* @return
* 	Amount of elements
*/
        int size() const;

/**
*	operator[]: Return element from Template Dynamic  Array
*
* @param
* index - The index of the element
* @return
* 	Reference to the element
* @exception
*   Return BadAccess for invalid read of memory.
*/
        T &operator[](int index);

/**
*	operator[]: Return a const element from Array
*
* @param
* index - The index of the element
* @return
* 	Reference to the const element
* @exception
*   Return BadAccess for invalid read of memory.
*/
        const T &operator[](int index) const;

        void push_back(T value);

        void expand();

        void pop();

        void shrink();

        int quantity(){
            return current;
        }
    };


    template<class T>
    void DynamicArray<T>::pop() {
        if(current <= 0)
            return;
        current -= 1;
        if(current < size()/2)
            shrink();
   }

    template<class T>
    void DynamicArray<T>::shrink() {
        int new_size = size() / 2;
        T* new_data = new T[new_size];
        for (int i = 0; i < new_size; ++i){
            new_data[i] = data[i];
        }
        delete data;
        data = new_data;
        length = new_size;
    }

    template<class T>
    void DynamicArray<T>::expand() {
        int new_size = EXPAND_FACTOR* size();
        T* new_data = new T[new_size];
        for (int i = 0; i < size(); ++i){
            new_data[i] = data[i];
        }
        delete data;
        data = new_data;
        length = new_size;
    }

    template<class T>
    void DynamicArray<T>::push_back(T value){
        if(size() == current)
            expand();
        data[current] = value;
        current++;
    }

template<class T>
    DynamicArray<T>::DynamicArray(int size) {
        data = new T[size];
        length = size;
        current = 0;
    }

    template<class T>
    DynamicArray<T>::DynamicArray(const DynamicArray<T> &a) {
        data = new T[a.size()];
        length = a.size();
        current = a.current;
        for (int i = 0; i < a.size(); ++i) {
            data[i] = a[i];
        }
    }

    template<class T>
    DynamicArray<T>::~DynamicArray() {
        delete[] data;
    }

    template<class T>
    DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &a) {
        if (this == &a) {
            return *this;
        }
        T *temp_array = new T[a.size()];
        delete[] data;
        for (int i = 0; i < a.size(); ++i) {
            try {
                temp_array[i] = a[i];
            }
            catch (const std::exception &e) {
                delete[] temp_array;
                throw e;
            }
        }
        data = temp_array;
        length = a.size();
        current = a.current;
        return *this;
    }

    template<class T>
    int DynamicArray<T>::size() const {
        return length;
    }

    template<class T>
    T &DynamicArray<T>::operator[](int index) {
        if (index < 0 || index >= this->current) {
            throw DynamicArray::BadAccess();
        }
        return data[index];
    }

    template<class T>
    const T &DynamicArray<T>::operator[](int index) const {
        if (index < 0 || index >= this->current) {
            throw DynamicArray::BadAccess();
        }
        return data[index];
    }


/**
* Exception Bad Access
*
* Implements of an exception class indicating a bad access to memory,
* which Inherit from std::exception.
*
* The following functions are available:
*   the big three - constructor , destructor and copy constructor(default).
*   what		- Return info on the exception.
*/
    template <class T>
    class DynamicArray<T>::BadAccess : public std::exception {
    public:
        const char* what() const noexcept override
        {
            return "Bad Access";
        }
    };


#endif //HW2_DYNAMICARRAY_H
