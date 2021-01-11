#ifndef GENERIC_AVL_H
#define GENERIC_AVL_H

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
    AVLNode<T>* get_root() const { return my_root; }
    AVLNode<T>* find_min(AVLNode<T>* root);
    AVLNode<T>* insert_value(const T& value);

    void in_order (AVLNode<T>* root) const;
    int calc_rank(AVLNode<T>* root, const T& value) const;
    void update_sub_delete(AVLNode<T>* node);
    AVLNode<T>* balance_sub_tree(AVLNode<T>* root);

    bool delete_value(AVLNode<T>* root, const T &value);
    void delete_node(AVLNode<T>* node);
    AVLNode<T>* remove_node_with_two_child(AVLNode<T>* node, bool delete_node = true);
    AVLNode<T>* remove_root();

    int get_nodes_counter() { return nodes_counter; }

    T getIthElement(AVLNode<T>* root, int i);

private:
    AVLNode<T>* my_root;
    int nodes_counter;
    AVLNode<T>* insert_node(AVLNode<T>* root, const T& value, AVLNode<T>* new_node);
    AVLNode<T>* rotate_left (AVLNode<T>* current_node);
    AVLNode<T>* rotate_right(AVLNode<T>* current_node);

    int get_balance_factor(AVLNode<T>* current_node) const;
    int get_tree_height(AVLNode<T>* root) const;

    static void update_height_and_balanced(AVLNode<T>* node){
        if(node == nullptr)
            return;
        int balance = AVLNode<T>::get_height(node->get_left()) - AVLNode<T>::get_height(node->get_right());
        node->set_balanced_factor(balance);
        node->set_height(max(AVLNode<T>::get_height(node->get_left()), AVLNode<T>::get_height(node->get_right())) + 1);
    }

    static void update_num_sub(AVLNode<T>* node){
        if(node == nullptr)
            return;
        int left_sub = 0, right_sub = 0;
        if(node->get_left() != nullptr)
            left_sub = node->get_left()->num_sub_tree;
        if(node->get_right() != nullptr)
            right_sub = node->get_right()->num_sub_tree;
        int num_sub = left_sub + right_sub + 1;
        node->num_sub_tree = num_sub;
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
AVLTree<T>::~AVLTree() {

    if(my_root)
        delete_node(my_root);
}

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
        if(node != nullptr)
            return node;
        AVLNode<T>* new_node = new AVLNode<T>(value);

        return (insert_node(my_root, value, new_node));
    }
}

template <class T>
AVLNode<T>* AVLTree<T>::insert_node(AVLNode<T>* root, const T& value, AVLNode<T>* new_node) {
    if(root->get_value() == value)
        return root;
    else if(value < root->get_value()) {
        // If there is a left child, keep going left.
        root->num_sub_tree++;
        if(root->get_left())
            insert_node(root->get_left(), value, new_node);
        else {
            root->set_left(new_node);
            new_node->set_parent(root);
            nodes_counter++;
        }
    }
    else {
        // If there is a right child, keep going right.
        root->num_sub_tree++;
        if(root->get_right())
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

template <class T>
void AVLTree<T>::in_order(AVLNode<T>* root) const {

    if(nodes_counter <= 0)
        return;
    if(root) {
        in_order(root->get_left());
        root->print_node(calc_rank(my_root, root->get_value()));
        in_order(root->get_right());
    }
}

template <class T>
int AVLTree<T>::calc_rank(AVLNode<T>* root, const T& value) const {
    AVLNode<T>* temp = root;
    int rank = 0;
    while(temp) {
        if(temp->get_value() > value)
            temp = temp->get_left();
        else if(temp->get_value() < value) {
            if(temp->get_left() == nullptr)
                rank += 1;
            else
                rank += 1 + temp->get_left()->num_sub_tree;
            temp = temp->get_right();
        } else {
            if(temp->get_left() != nullptr)
                rank += 1 + temp->get_left()->num_sub_tree;
            else
                rank += 1;
            break;
        }
    }
    return rank;
}

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

template <class T>
AVLNode<T>* AVLTree<T>::rotate_left(AVLNode<T>* current_node) {

    AVLNode<T>* new_root = current_node->get_right();
    current_node->set_right(new_root->get_left());
    if(new_root->get_left())
        (new_root->get_left())->set_parent(current_node);
    current_node->set_right(new_root->get_left());
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
    AVLTree<T>::update_height_and_balanced(current_node);
    AVLTree<T>::update_num_sub(current_node);
    return new_root;
}

template <class T>
AVLNode<T>* AVLTree<T>::rotate_right(AVLNode<T>* current_node) {

    // Rotate node
    AVLNode<T>* new_root = current_node->get_left();
    current_node->set_left(new_root->get_right());
    if(new_root->get_right())
        (new_root->get_right())->set_parent(current_node);
    current_node->set_left(new_root->get_right());
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
    AVLTree<T>::update_height_and_balanced(current_node);
    AVLTree<T>::update_num_sub(current_node);
    return new_root;
}

template <class T>
bool AVLTree<T>::delete_value(AVLNode<T>* root, const T &value) {

    if(root == nullptr)
        return false;
    AVLNode<T>* temp_node = find_value(root, value);
    // value not in tree
    if(temp_node == nullptr)
        return false;
    update_sub_delete(temp_node);
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
    while (temp_node) {
        temp_node = balance_sub_tree(temp_node);
        update_num_sub(temp_node);
    }


    return true; // removed succeed.
}

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

template<class T>
void AVLTree<T>::update_sub_delete(AVLNode<T>* node) {

    AVLNode<T>* temp = node->get_parent();
    while(temp) {
        temp->num_sub_tree--;
        temp = temp->get_parent();
    }
}

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

    // We update the height and balanced factor of the node and its children after the roll
    auto left = root->get_left();
    auto right = root->get_right();
    if(left != nullptr) {
        balance = get_tree_height(left->get_left()) - get_tree_height(left->get_right());
        left->set_balanced_factor(balance);
        left->set_height(max(get_tree_height(left->get_left()), get_tree_height(left->get_right())) + 1);
    }
    if(right != nullptr) {
        balance = get_tree_height(right->get_left()) - get_tree_height(right->get_right());
        right->set_balanced_factor(balance);
        right->set_height(max(get_tree_height(right->get_left()), get_tree_height(right->get_right())) + 1);
    }

    balance = get_tree_height(root->get_left()) - get_tree_height(root->get_right());
    root->set_balanced_factor(balance);
    root->set_height(max(get_tree_height(root->get_left()), get_tree_height(root->get_right())) + 1);
    return root->get_parent();
}

template<class T>
T AVLTree<T>::getIthElement(AVLNode<T>* root, int i) {
    if (root == nullptr)
        return T();
    if(root->num_sub_tree < i)
        return T();
    AVLNode<T>* tmp = root;
    while (tmp){
        int left_sub_tree = 0;
        if(tmp->get_left() != nullptr)
            left_sub_tree = tmp->get_left()->num_sub_tree;
        if(i < left_sub_tree + 1)
            tmp = tmp->get_left();
        else if( i > left_sub_tree + 1){
            tmp = tmp->get_right();
            i = i - left_sub_tree - 1;
        }else if( i == left_sub_tree + 1)
            return  tmp->data;
    }
    return T();//will  not get to here
}

#endif // GENERIC_AVL_H