#ifndef GENERIC_AVL_H
#define GENERIC_AVL_H

#include <iostream>
#include "AVLNode.h"
#include "Node.h"

template <class T>
static int max(T a, T b) {
    return (a > b) ? a : b;
}

template<class T>
static AVLNode<T>* remove_leaf(AVLNode<T>* node, bool delete_node = true);

template<class T>
static AVLNode<T>* remove_node_with_one_child(AVLNode<T>* node, bool delete_node = true);

template <class T>
class AVLTree {
public:
    explicit AVLTree() : my_root(nullptr), nodes_counter(0) {}
    ~AVLTree();
    AVLNode<T>* find_value(AVLNode<T>* root, const T& value) const;
    bool delete_value(AVLNode<T>* root, const T &value);
    AVLNode<T>* get_root() const { return my_root; }
    AVLNode<T>* find_min(AVLNode<T>* root);
    AVLNode<T>* find_max(AVLNode<T>* root);

    void reverse_in_order_empty(AVLNode<T>* root, int* remained, int* counted, int *courses, int *classes) const;
    void reverse_in_order(AVLNode<T>* root, int* remained, int* counted, int *courses, int *classes) const;
    void in_order (AVLNode<T>* root) const;
    AVLNode<T>* insert_value(const T& value);
    void delete_node(AVLNode<T>* node);
    AVLNode<T>* remove_root();
    AVLNode<T>* balance_sub_tree(AVLNode<T>* root);
    AVLNode<T>* remove_node_with_two_child(AVLNode<T>* node, bool delete_node = true);
private:
    AVLNode<T>* my_root;
    int nodes_counter;
    AVLNode<T>* rotate_left (AVLNode<T>* current_node);
    AVLNode<T>* rotate_right(AVLNode<T>* current_node);
    AVLNode<T>* insert_node(AVLNode<T>* root,const T& value, AVLNode<T>* new_node);

    int get_balance_factor(AVLNode<T>* current_node) const;
    int get_tree_height(AVLNode<T>* root) const;
    static void update_height_and_balanced(AVLNode<T>* node){
        if(node == nullptr)
            return;
        int balance = AVLNode<T>::get_height(node->get_left()) - AVLNode<T>::get_height(node->get_right());
        node->set_balanced_factor(balance);
        node->set_height(max(AVLNode<T>::get_height(node->get_left()), AVLNode<T>::get_height(node->get_right())) + 1);
    }
};

template <class T>
AVLNode<T>* AVLTree<T>::find_min(AVLNode<T>* root) {

    if(nodes_counter <= 0)
        return nullptr;
    if(root == nullptr)
        return nullptr;
    else if(root->get_left() == nullptr)
        return root;
    else
        return find_min(root->get_left());
}

template <class T>
AVLNode<T>* AVLTree<T>::find_max(AVLNode<T>* root) {

    if(nodes_counter <= 0)
        return nullptr;
    if(root == nullptr)
        return nullptr;
    else if(root->get_right() == nullptr)
        return root;
    else
        return find_max(root->get_right());
}

template <class T>
AVLTree<T>::~AVLTree() {

    if(my_root)
        delete_node(my_root);
}

/***
 *
 * @tparam T
 * @param node
 */
template <class T>
void AVLTree<T>::delete_node(AVLNode<T>* node) {

    // deletes all subtree of node and node itself.
    if(nodes_counter <= 0)
        return;
    if(node) {
        delete_node(node->get_left());
        delete_node(node->get_right());
        delete node;
        nodes_counter--;
    }
}

template <class T>
AVLNode<T>* AVLTree<T>::insert_value(const T& value) {

    if(my_root == nullptr || nodes_counter == 0) {
        // Creating a root, if tree is empty.
        auto* new_node = new AVLNode<T>(value);
        my_root = new_node;
        nodes_counter++;
        return new_node;
    }
    else {
        auto node = find_value(my_root,value);
        if(node != nullptr){
            return node;
        }
        AVLNode<T>* new_node = new AVLNode<T>(value);

        return (insert_node(my_root,value, new_node));
    }
}

/***
 *
 * @tparam T
 * @param root
 * @param value
 * @param new_node
 * @return the new node that we inserted
 */
template <class T>
AVLNode<T>* AVLTree<T>::insert_node(AVLNode<T>* root, const T& value, AVLNode<T>* new_node) {
    if(root->get_value() == value)
        return root;
    else if(value < root->get_value()) {
        if(root->get_left()) // If there is a left child, keep going left.
            insert_node(root->get_left(), value, new_node);
        else {
            //new_node.data = (value);
            root->set_left(new_node);
            new_node->set_parent(root);
            nodes_counter++;
        }
    }
    else {
        if(root->get_right()) // If there is a right child, keep going right.
            insert_node(root->get_right(), value, new_node);
        else {
            root->set_right(new_node);
            new_node->set_parent(root);
            nodes_counter++;
        }
    }

    // Balance the tree.
    int balance = get_tree_height(root->get_left()) - get_tree_height(root->get_right());
    root->set_balanced_factor(balance);
    if(balance > 1) { // Left tree is unbalanced
        if(get_balance_factor(root->get_left()) < 0) // LR rotation needed.
            rotate_left(root->get_left());
        rotate_right(root);
    }
    else if(balance < -1) { // Right tree is unbalanced.
        if(get_balance_factor(root->get_right()) > 0) // RL rotation needed.
            rotate_right(root->get_right());
        rotate_left(root);
    }

    balance = get_tree_height(root->get_left()) - get_tree_height(root->get_right());
    root->set_balanced_factor(balance);
    root->set_height(max(get_tree_height(root->get_left()), get_tree_height(root->get_right())) + 1);
    new_node->set_height(max(get_tree_height(new_node->get_left()), get_tree_height(new_node->get_right())) + 1);
    new_node->set_balanced_factor(get_tree_height(new_node->get_left()) - get_tree_height(new_node->get_right()));
    return new_node;
}

/***
 *
 * @tparam T
 * @param root
 */
template <class T>
void AVLTree<T>::in_order(AVLNode<T>* root) const {

    if(nodes_counter <= 0)
        return;
    if(root) {
        in_order(root->get_left());
        root->print_node();
        in_order(root->get_right());
    }
}

/***
 *
 * @tparam T
 * @param root
 * @param remained
 * @param counted
 * @param courses
 * @param classes
 */
template <class T>
void AVLTree<T>::reverse_in_order(AVLNode<T>* root, int* remained, int* counted, int *courses, int *classes) const {

    if(root) {
        reverse_in_order(root->get_right(), remained, counted, courses, classes);
        if(*remained <= 0)
            return;
        // root->print_node();
        courses[*counted] = root->data.getCourse();
        classes[*counted] = root->data.getLecture();
        *remained = *remained - 1;
        *counted = *counted + 1;
        reverse_in_order(root->get_left(), remained, counted, courses, classes);
    }
}

/***
 *
 * @tparam T
 * @param root
 * @param remained
 * @param counted
 * @param courses
 * @param classes
 */
template<class T>
void AVLTree<T>::reverse_in_order_empty(AVLNode<T> *root, int *remained, int *counted, int *courses, int *classes) const {

    if(root) {
        reverse_in_order_empty(root->get_right(), remained, counted, courses, classes);
        if(*remained <= 0)
            return;
        // root->print_node();
        Node<int>* head_list = root->data.getCoursePtr()->data.empty_lecture.head;
        while (head_list && *remained > 0) {
            courses[*counted] = root->data.getCourseID();
            classes[*counted] = head_list->getData();
            head_list = head_list->getNext();
            *remained = *remained - 1;
            *counted = *counted + 1;
        }
        reverse_in_order_empty(root->get_left(), remained, counted, courses, classes);
    }
}

/***
 *
 * @tparam T
 * @param root
 * @param value
 * @return pointer to the node with the wanted value
 */
template <class T>
AVLNode<T>* AVLTree<T>::find_value(AVLNode<T>* root, const T& value) const {

    if(root) {
        if (root->get_value() == value)
            return root;
        else if (value < root->get_value())
            return find_value(root->get_left(), value);
        else
            return find_value(root->get_right(), value);
    }
    return nullptr;
}

template <class T>
int AVLTree<T>::get_tree_height(AVLNode<T>* root) const {

    if(root == nullptr)
        return -1;
    return AVLNode<T>::get_height(root);
}

template <class T>
int AVLTree<T>::get_balance_factor(AVLNode<T>* current_node) const {
    if(current_node == nullptr)
        return 0;
    return current_node->get_balance_factor();
}

/***
 *
 * @tparam T
 * @param current_node
 * @return the root of the new  sub_tree
 */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_left(AVLNode<T>* current_node) {

    AVLNode<T>* new_root = current_node->get_right();
    current_node->set_right(new_root->get_left());
    if(new_root->get_left())
        (new_root->get_left())->set_parent(current_node);
    current_node->set_right(new_root->get_left()); /////
    if(current_node->get_parent() == nullptr) {
        my_root = new_root;
        new_root->set_parent(nullptr);
    }
    else {
        if(current_node->get_parent()->get_left() == current_node)
            current_node->get_parent()->set_left(new_root);
        else
            current_node->get_parent()->set_right(new_root);
        new_root->set_parent(current_node->get_parent());
    }
    new_root->set_left(current_node);
    current_node->set_parent(new_root);
    AVLTree<T>::update_height_and_balanced(current_node); /////
    return new_root;
}

/***
 *
 * @tparam T
 * @param current_node
 * @return the root  of the new sub_tree
 */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_right(AVLNode<T>* current_node) {

    // Rotate node
    AVLNode<T>* new_root = current_node->get_left();
    current_node->set_left(new_root->get_right());
    if(new_root->get_right())
        (new_root->get_right())->set_parent(current_node);
    current_node->set_left(new_root->get_right());/////////
    // Adjust tree
    if(current_node->get_parent() == nullptr) {
        my_root = new_root;
        new_root->set_parent(nullptr);
    }
    else {
        if(current_node->get_parent()->get_left() == current_node)
            current_node->get_parent()->set_left(new_root);
        else
            current_node->get_parent()->set_right(new_root);
        new_root->set_parent(current_node->get_parent());
    }
    new_root->set_right(current_node);
    current_node->set_parent(new_root);
    AVLTree<T>::update_height_and_balanced(current_node);////////
    return new_root;
}

/***
 *
 * @tparam T
 * @param root
 * @param value
 * @return true if we did remove a node
 */
template <class T>
bool AVLTree<T>::delete_value(AVLNode<T>* root, const T &value) {

    if(root == nullptr)
        return false;
    AVLNode<T>* temp_node = find_value(root, value);
    // value not in tree
    if(temp_node == nullptr)
        return false;
    AVLNode<T>* left = temp_node->get_left();
    AVLNode<T>* right = temp_node->get_right();
    if(temp_node == my_root) { //the node we removing is the root
        temp_node = remove_root();
        nodes_counter++; // because remove_root already update the node_counter
    } else if(left == nullptr && right == nullptr) // we removing a leaf
        temp_node = remove_leaf(temp_node);
    else if(left == nullptr || right == nullptr)  // we removing a node with one child
        temp_node = remove_node_with_one_child(temp_node);
    else // we removing a node with two child
        temp_node = remove_node_with_two_child(temp_node);

    nodes_counter--;
    /// we need to roll and fix the tree;

    // Balance the tree.
    while (temp_node)
        temp_node = balance_sub_tree(temp_node);

    return true; // removed succeed.
}

/***
 *
 * @tparam T
 * @param node
 * @param delete_node
 * @return the node to start the rolls from
 */
template<class T>
AVLNode<T>* remove_leaf(AVLNode<T>* node, bool delete_node) {

    AVLNode<T> *parent = node->get_parent();
    // we are left child
    if(node->get_parent()->get_left() == node)
        node->get_parent()->set_left(nullptr);
    else // we are right child
        node->get_parent()->set_right(nullptr);
    if (delete_node)
        delete node;
    return parent;
}

/***
 *
 * @tparam T
 * @param node
 * @param delete_node
 * @return the node to start the rolls from
 */
template<class T>
static AVLNode<T>* remove_node_with_one_child(AVLNode<T>* node, bool delete_node) {

    AVLNode<T>* parent = node->get_parent();
    AVLNode<T>* left = node->get_left();
    AVLNode<T>* right = node->get_right();

    // we are left child.
    if(node->get_parent()->get_left() == node) {
        // we have right child.
        if(left == nullptr) {
            node->get_parent()->set_left(right);
            right->set_parent(node->get_parent());
            if (delete_node)
                delete node;
            //return parent;
            return parent;
        }
        else { // we have left child.
            node->get_parent()->set_left(left);
            left->set_parent(node->get_parent());
            if (delete_node)
                delete node;
            //return parent;
            return parent;
        }
    }
    else { // we are right child.
        if(left == nullptr) { // we have right child
            node->get_parent()->set_right(right);
            right->set_parent(node->get_parent());
            if (delete_node)
                delete node;
            //return parent;
            return parent;
        }
        else { // we have left child.
            node->get_parent()->set_right(left);
            left->set_parent(node->get_parent());
            if (delete_node)
                delete node;
            // return parent;
            return parent;
        }
    }
}

/**
 *
 * @tparam T
 * @param node
 * @param delete_node
 * @return the node to start thr rolls from
 */
template<class T>
AVLNode<T>* AVLTree<T>::remove_node_with_two_child(AVLNode<T>* node, bool delete_node) {

    AVLNode<T>* left = node->get_left();
    AVLNode<T>* right = node->get_right();
    AVLNode<T>* next_in_order = find_min(right);
    if(next_in_order->get_right() == nullptr)
        remove_leaf(next_in_order, false);
    else
        remove_node_with_one_child(next_in_order, false);
    if(next_in_order->get_parent() == node) { // the next in order node is the right child of the node we want to delete
        next_in_order->set_parent(node->get_parent());
        if(node->get_parent()->get_left() == node) // node is a left child
            node->get_parent()->set_left(next_in_order);
        else // node is a right child
            node->get_parent()->set_right(next_in_order);
        next_in_order->set_left(left);
        left->set_parent(next_in_order);
        next_in_order->set_right(node->get_right());
        if(node->get_right()!= nullptr)
            node->get_right()->set_parent(next_in_order);
        if(delete_node)
            delete node;
        return next_in_order;
    }
    next_in_order->get_parent()->set_left(next_in_order->get_right());
    if(next_in_order->get_right() != nullptr)
        next_in_order->get_right()->set_parent(next_in_order->get_parent());
    AVLNode<T>* Node_to_fix_roll_from = next_in_order->get_parent();
    next_in_order->set_left(left);
    next_in_order->set_right(right);
    next_in_order->set_parent(node->get_parent());
    if(node->get_parent()->get_left() == node) // node is a left child
        node->get_parent()->set_left(next_in_order);
    else // node is a right child
        node->get_parent()->set_right(next_in_order);

    left->set_parent(next_in_order);
    right->set_parent(next_in_order);
    if(delete_node)
        delete node;
    return Node_to_fix_roll_from;
}

/***
 *
 * @tparam T
 * @return pointer to the new root
 */
template<class T>
AVLNode<T> *AVLTree<T>::remove_root() {

    AVLNode<T>* node = my_root;
    AVLNode<T>* left = node->get_left();
    AVLNode<T>* right = node->get_right();
    // we have no children.
    if (left == nullptr && right == nullptr) {
        delete node;
        my_root = nullptr;
        nodes_counter = 0;
        return nullptr;
    }
        //we have one child
    else if(left == nullptr || right == nullptr) {
        if(left != nullptr){
            my_root = left;
            left->set_parent(nullptr);
        }
        else {
            my_root = right;
            right->set_parent(nullptr);
        }
        delete node;
        nodes_counter--;
        return my_root;
    }
        // we have two children
    else {
        AVLNode<T>* next_in_order = find_min(right);
        //next node in order is the right node from the root
        if(next_in_order->get_parent() == node) {
            next_in_order->set_parent(nullptr);
            next_in_order->set_left(node->get_left());
            node->get_left()->set_parent(next_in_order);
            delete node;
            my_root = next_in_order;
            nodes_counter--;
            return my_root;
        }
        //next in order node is a leaf
        if(next_in_order->get_right() == nullptr)
            remove_leaf(next_in_order, false);
        else
            remove_node_with_one_child(next_in_order, false);
        next_in_order->get_parent()->set_left(next_in_order->get_right());
        if(next_in_order->get_right() != nullptr)
            next_in_order->get_right()->set_parent(next_in_order->get_parent());
        AVLNode<T>* Node_to_fix_roll_from = next_in_order->get_parent();
        next_in_order->set_left(left);
        next_in_order->set_right(right);
        next_in_order->set_parent(nullptr);
        left->set_parent(next_in_order);
        right->set_parent(next_in_order);
        delete node;
        my_root = next_in_order;
        nodes_counter--;
        return Node_to_fix_roll_from;
    }
}

/***
 *
 * @tparam T
 * @param root
 * @return hte node to start the rolls from
 */
template<class T>
AVLNode<T>* AVLTree<T>::balance_sub_tree(AVLNode<T>* root) {

    int balance = get_tree_height(root->get_left()) - get_tree_height(root->get_right());
    root->set_balanced_factor(balance);
    if(balance > 1) { // Left tree is unbalanced
        if(get_balance_factor(root->get_left()) < 0) // LR rotation needed.
            rotate_left(root->get_left());
        rotate_right(root);
    }
    else if(balance < -1) { // Right tree is unbalanced.
        if(get_balance_factor(root->get_right()) > 0) // RL rotation needed.
            rotate_right(root->get_right());
        rotate_left(root);
    }

    //we update the height and balanced factor of the node and its childs after the roll
    auto left = root->get_left();
    auto right = root->get_right();
    if(left != nullptr){
        balance = get_tree_height(left->get_left()) - get_tree_height(left->get_right());
        left->set_balanced_factor(balance);
        left->set_height(max(get_tree_height(left->get_left()), get_tree_height(left->get_right())) + 1);
    }
    if(right != nullptr){
        balance = get_tree_height(right->get_left()) - get_tree_height(right->get_right());
        right->set_balanced_factor(balance);
        right->set_height(max(get_tree_height(right->get_left()), get_tree_height(right->get_right())) + 1);
    }

    balance = get_tree_height(root->get_left()) - get_tree_height(root->get_right());
    root->set_balanced_factor(balance);
    root->set_height(max(get_tree_height(root->get_left()), get_tree_height(root->get_right())) + 1);
    return root->get_parent();
}

#endif // GENERIC_AVL_H