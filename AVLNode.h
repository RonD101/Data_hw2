#ifndef AVLNODE_H
#define AVLNODE_H

template <class T>
class AVLNode {
public:
    explicit AVLNode(const T& value) : data(value), left(nullptr), right(nullptr), parent(nullptr), height(0), balance_factor(0) {}
    ~AVLNode() = default;
    T data;

    void set_balanced_factor(int new_balance_factor) { balance_factor = new_balance_factor; }
    void set_parent(AVLNode* new_parent) { this->parent = new_parent; }
    void set_right(AVLNode* new_right)   { this->right = new_right;}
    void set_left(AVLNode* new_left)     { this->left = new_left;}
    void set_height(int new_height)      { this->height = new_height; }

    const T& get_value() const           { return data; }
    int get_balance_factor() const       { return balance_factor; }
    int static get_height(AVLNode* root);

    void print_node() const { std::cout << data << std::endl; }
    AVLNode* get_parent() const { return parent; }
    AVLNode* get_right()  const { return right; }
    AVLNode* get_left()   const { return left; }
    static void update_height_and_balanced(AVLNode<T>* node){
        if(node == nullptr)
            return;
        int L_height = -1, R_height = -1;
        if (node->get_left() != nullptr)
            L_height = get_height(node->get_left());
        if(node->get_right() != nullptr)
            R_height = get_height(node->get_right());
        int balance = L_height - R_height;
        node->set_balanced_factor(balance);
        node->set_height(max(get_height(node->get_left()), get_height(node->get_right())) + 1);
    }

private:
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    int height;
    int balance_factor;
};

template <class T>
int AVLNode<T>::get_height(AVLNode* root) {
    if(root == nullptr)
        return -1;
    return root->height;
}
#endif // AVLNODE_H