#ifndef HW2_NODE_H
#define HW2_NODE_H

template<class T>
class Node {
    T data;
    Node* nextNode;
    Node* prevNode;
public:
    explicit Node(T set_data = T()) : data(set_data), nextNode(nullptr), prevNode(nullptr) {}

    void setNext(Node<T>* next_Node) { nextNode = next_Node; }
    void setPrev(Node<T>* prev_Node) { prevNode = prev_Node; }

    Node<T>* getNext() { return nextNode; }
    Node<T>* getPrev() { return prevNode; }

    T setData(T new_data)   { data = new_data; }
    T* getDataAddress()     { return &data; }
    T getData()             { return data; }
};

#endif //HW2_NODE_H