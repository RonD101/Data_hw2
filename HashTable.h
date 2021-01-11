//
// Created by Ron Dahan on 20/06/2020.
//

#ifndef HW2_HASHTABLE_H
#define HW2_HASHTABLE_H

#include <iostream>
#include "List.h"
#include <string>

/**
* Hash Table
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


namespace mtm {
    template<class T>
    class HashTable {
        T *data;
        int length;
    public:
        class BadAccess;

/**
*	Constructor: create a new Hash Table
*
* @param
* size - The Initial size of the Array(optional)
* @return
* 	The new Array
* @assumption
*   There is a default constructor for class T.
*/
        explicit HashTable(int size = 10);

/**
*	Copy Constructor: create a copy Array
*
* @param
* HashTable - The Hash Table which we copy the values from.
* @return
* 	The copied Array
* @assumption
*   There is a default constructor for class T.
*   There is a '=' operator implement for class T.
*/
        HashTable(const HashTable<T> &a);

/**
*    Destructor: Destroy the Hash Table when her 'life' end.
*
* @return
* 	No Return Value.
* @assumption
*   There is a default destructor for class T.
*/
        ~HashTable();

/**
*	operator=: assign Hash Table
*
* @param
* HashTable - The Hash Table which we copy the values from.
* @return
* 	The assigned array
* @assumption
*   There is a default constructor for class T.
*   There is a default destructor for class T.
*   There is a '=' operator implement for class T.
*/
        HashTable &operator=(const HashTable<T> &a);

/**
*	size: Returns the amount of element in array.
*
* @return
* 	Amount of elements
*/
        int size() const;

/**
*	operator[]: Return element from Hash Table
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
    };

    template<class T>
    HashTable<T>::HashTable(int size) {
        data = new T[size];
        length = size;
    }

    template<class T>
    HashTable<T>::HashTable(const HashTable<T> &a) {
        data = new T[a.size()];
        length = a.size();
        for (int i = 0; i < a.size(); ++i) {
            data[i] = a[i];
        }
    }

    template<class T>
    HashTable<T>::~HashTable() {
        delete[] data;
    }

    template<class T>
    HashTable<T>& HashTable<T>::operator=(const HashTable<T> &a) {
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
        return *this;
    }

    template<class T>
    int HashTable<T>::size() const {
        return length;
    }

    template<class T>
    T &HashTable<T>::operator[](int index) {
        if (index < 0 || index >= this->size()) {
            throw HashTable::BadAccess();
        }
        return data[index];
    }

    template<class T>
    const T &HashTable<T>::operator[](int index) const {
        if (index < 0 || index >= this->size()) {
            throw HashTable::BadAccess();
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
    class HashTable<T>::BadAccess : public std::exception {
    public:
        const char* what() const noexcept override
        {
            return "Bad Access";
        }
    };
}

#endif //HW2_HASHTABLE_H
