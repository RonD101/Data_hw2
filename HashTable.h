//
// Created by Ron Dahan on 20/06/2020.
//

#ifndef HW2_HASHTABLE_H
#define HW2_HASHTABLE_H
#define EXPAND_FACTOR 2

#include <iostream>
#include "List.h"
#include <string>

/**
* Hash Table
*
* Implements a generic typed HashTable.
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
    class HashTable {
        List<T> *data;
        int length;
        int quantity;
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
        explicit HashTable(int size = 2);

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
       // T &operator[](int index);

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
        //const T &operator[](int index) const;

        void insert(T value);

        T* search(T value);

        void remove(T value);

        void expand();

        void shrink();

        friend std::ostream& operator<<(std::ostream& os, const HashTable<T>& hash){
            for (int i = 0; i < hash.size(); ++i) {
            os << "Row number " << i << ": ";
            Node<T>* currentHead = hash.data[i].head;
            while (currentHead != nullptr){
                os << currentHead->getData() << " -> ";
                currentHead = currentHead->getNext();
            }
            os << "NULL" << std::endl;
            }
            return os;
        }

    };



    template<class T>
    HashTable<T>::HashTable(int size) {
        data = new List<T>[size];
        length = size;
        quantity = 0;
    }

    template<class T>
    HashTable<T>::HashTable(const HashTable<T> &a) {
        data = new T[a.size()];
        length = a.size();
        quantity = a.quantity;
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
        quantity = a.quantity;
        return *this;
    }

    template<class T>
    int HashTable<T>::size() const {
        return length;
    }

    /*
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
    }*/


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

template<class T>
void HashTable<T>::insert(T value) {
    if(search(value) != nullptr)
        return;
    if(quantity == size())
        expand();
    data[value%size()].addAtStart(value);
    quantity += 1;
}

template<class T>
void HashTable<T>::expand() {
    int new_size = EXPAND_FACTOR* size();
    List<T> *new_data = new List<T>[new_size];
    for (int i = 0; i < size(); ++i){
        Node<T>* currentHead = data[i].head;
        while (currentHead != nullptr){
            new_data[currentHead->getData()%new_size].addAtStart(currentHead->getData());
            currentHead  = currentHead->getNext();
        }
    }
    delete[] data;
    data = new_data;
    length = new_size;
}

template<class T>
void HashTable<T>::remove(T value) {
    Node<T>* currentHead = data[value%size()].head;
    while (currentHead != nullptr){
        if(currentHead->getData() == value) {
            data[value % size()].removeNode(currentHead);
            quantity -= 1;
            if(quantity < size()/(2* EXPAND_FACTOR))
                shrink();
            return;
        }
        currentHead = currentHead->getNext();
    }
}

template<class T>
void HashTable<T>::shrink() {
    int new_size = size() / EXPAND_FACTOR;
    List<T> *new_data = new List<T>[new_size];
    for (int i = 0; i < size(); ++i){
        Node<T>* currentHead = data[i].head;
        while (currentHead != nullptr){
            new_data[currentHead->getData()%new_size].addAtStart(currentHead->getData());
            currentHead  = currentHead->getNext();
        }
    }
    delete[] data;
    data = new_data;
    length = new_size;
}

template<class T>
T *HashTable<T>::search(T value) {
    Node<T>* currentHead = data[value%size()].head;
    while (currentHead != nullptr){
        if(currentHead->getData() == value) {
            return currentHead->getDataAddress();
        }
        currentHead = currentHead->getNext();
    }
    return nullptr;
}


#endif //HW2_HASHTABLE_H
