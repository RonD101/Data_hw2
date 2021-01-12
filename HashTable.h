#ifndef HW2_HASHTABLE_H
#define HW2_HASHTABLE_H
#define EXPAND_FACTOR 2

#include "List.h"

template<class T>
class HashTable {
    List<T> *data;
    int length;
    int quantity;
public:
    class BadAccess;
    explicit HashTable(int size = 2);
    HashTable(const HashTable<T> &a);
    ~HashTable();
    HashTable &operator=(const HashTable<T> &a);
    int size() const;
    bool insert(T value);
    void remove(T value);
    void expand();
    void shrink();
    T* search(T value);
    friend std::ostream& operator<<(std::ostream& os, const HashTable<T>& hash){
        for (int i = 0; i < hash.size(); ++i) {
            os << "Row number " << i << ": ";
            Node<T>* currentHead = hash.data[i].head;
            while (currentHead != nullptr) {
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
    for (int i = 0; i < a.size(); ++i)
        data[i] = a[i];
}

template<class T>
HashTable<T>::~HashTable() {
    delete[] data;
}

template<class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T> &a) {
    if (this == &a)
        return *this;
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

template <class T>
class HashTable<T>::BadAccess : public std::exception {
public:
    const char* what() const noexcept override {
        return "Bad Access";
    }
};

template<class T>
bool HashTable<T>::insert(T value) {
    if(search(value) != nullptr)
        return false;
    if(quantity == size())
        expand();
    data[value % size()].addAtStart(value);
    quantity += 1;
    return true;
}

template<class T>
void HashTable<T>::expand() {
    int new_size = EXPAND_FACTOR * size();
    List<T> *new_data = new List<T>[new_size];
    for (int i = 0; i < size(); ++i) {
        Node<T>* currentHead = data[i].head;
        while (currentHead != nullptr) {
            new_data[currentHead->getData() % new_size].addAtStart(currentHead->getData());
            currentHead = currentHead->getNext();
        }
    }
    delete[] data;
    data = new_data;
    length = new_size;
}

template<class T>
void HashTable<T>::remove(T value) {
    Node<T>* currentHead = data[value % size()].head;
    while (currentHead != nullptr) {
        if(currentHead->getData() == value) {
            data[value % size()].removeNode(currentHead);
            quantity -= 1;
            if(quantity < size() / (2* EXPAND_FACTOR))
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
    for (int i = 0; i < size(); ++i) {
        Node<T>* currentHead = data[i].head;
        while (currentHead != nullptr) {
            new_data[currentHead->getData() % new_size].addAtStart(currentHead->getData());
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
    while (currentHead != nullptr) {
        if(currentHead->getData() == value)
            return currentHead->getDataAddress();
        currentHead = currentHead->getNext();
    }
    return nullptr;
}

#endif //HW2_HASHTABLE_H