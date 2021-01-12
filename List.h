#ifndef HW2_LIST_H
#define HW2_LIST_H

#include "Node.h"

template<class T>
class List {
    public:
        Node<T> *head;
        explicit List():head(nullptr){}
        ~List();
        Node<T>* addNodeAfter(Node<T> *node, T data);
        void addNodeBefore(Node<T> *node, T data);
        void removeNode(Node<T> *node);
        Node<T>* addAtStart(T data);
};

template <class T>
void List<T>::removeNode(Node<T> *node) {
    if(node == nullptr || head == nullptr)
        return;
    if(node == head) {
        // node is head with next nodes (more than one item).
        if(node->getNext() != nullptr) {
            head = node->getNext();
            head->setPrev(nullptr);
        } else
            head = nullptr;
        delete node;
        return;
    }
    // if node is not the last one.
    if(node->getNext() != nullptr) {
        node->getPrev()->setNext(node->getNext());
        node->getNext()->setPrev(node->getPrev());
    }
    else
        node->getPrev()->setNext(nullptr);
    delete node;
}

template<class T>
Node<T>* List<T>::addNodeAfter(Node<T> *node,T data) {
    if (node == nullptr)
        return nullptr;
    auto* new_node = new Node<T>(data);
    if(node->getNext() != nullptr) {
        (node->getNext())->setPrev(new_node);
        new_node->setNext(node->getNext());
    }
    new_node->setPrev(node);
    node->setNext(new_node);
    return new_node;
}

template<class T>
void List<T>::addNodeBefore(Node<T> *node, T data) {
    if(node == nullptr)
        return;
    Node<T>* new_node = new Node<T>(data);
    if(node->getPrev() != nullptr) {
        new_node->setPrev(node->getPrev());
        (node->getPrev())->setNext(new_node);
    }
    new_node->setNext(node);
    node->setNext(new_node);
}

template<class T>
Node<T>* List<T>::addAtStart(T data) {
    Node<T>* new_node = new Node<T>(data);
    if(head == nullptr) {
        head = new_node;
        head->setNext(nullptr);
        return new_node;
    }
    head->setPrev(new_node);
    new_node->setNext(head);
    head = new_node;
    return new_node;
}

template<class T>
List<T>::~List() {
    while (head) {
        Node<T>* tmp = head;
        head = head->getNext();
        delete tmp;
    }
}

#endif //HW2_LIST_H