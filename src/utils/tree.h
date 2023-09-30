/**
 * Copyright 2023, Brandon Chaney
 * Tree is an AVL implementation of a self balancing tree. This ADT is used
 * to tally the frequency of individual characters when creating a frequency
 * table from scratch.
 *
 * This implemenation follows the implementation in the textbook.
 *
 */

#pragma once
#include <cstdint>
#include <exception>

template <typename T>
class Tree {
 private:
    class TreeNode {
     public:
        using value_type = T;
        using pointer_type = T*;
        using reference = T&;
        using const_reference = const T&;

        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        uint32_t height;

        value_type data;

        TreeNode() {
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            height = 0;
            // data initialized to data type's default constructor
        }

        explicit TreeNode(value_type data) {
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            height = 0;
            // assuming that the copy constructor and assignment copy
            // constructors are defined for value_type
            this->data = data;
        }

        ~TreeNode() = default;

        TreeNode(const TreeNode& other) {
            parent = other.parent;
            left = other.left;
            right = other.right;
            // assuming that the assignment copy constructor is defined for
            // value_type
            data = other.data;
        }
    };

    using value_type = T;
    using pointer_type = T*;
    using reference = T&;
    using const_reference = const T&;

    using node_type = Tree<T>::TreeNode;
    using node_pointer = Tree<T>::TreeNode*;

    node_pointer root;
    int _size;

    reference get(reference);

    /// @brief updates the height of a node by taking the max height of its
    /// children and adding 1
    /// @param node
    void update_height(node_pointer node) {
        int left_height = -1;
        if (node->left != nullptr) {
            left_height = node->left->height;
        }

        int right_height = -1;
        if (node->right != nullptr) {
            right_height = node->right->height;
        }

        node->height = max(left_height, right_height) + 1;
    }

    /// @brief sets a new child as either the left or right child of the parent.
    /// This method also updates the height of the parent after adding the new
    /// child.
    /// @param parent a node recieving a new child
    /// @param which_child 0 for left child or 1 for right child
    /// @param new_child
    void set_child(node_pointer parent, int which_child,
                   node_pointer new_child) {
        // left child
        if (which_child == 0) {
            parent->left = new_child;
        } else {
            parent->right = new_child;
        }
        if (new_child != nullptr) {
            new_child->parent = parent;
        }

        update_height(parent);
    }

    /// @brief this method replaces a node's child with another node
    /// @param parent node with a child being replaced
    /// @param curr_node current child
    /// @param new_node new child
    void replace_child(node_pointer parent, node_pointer curr_node,
                       node_pointer new_node) {
        if (parent->left == curr_node) {
            set_child(parent, 0, new_node);
        } else if (parent->right == curr_node) {
            set_child(parent, 1, new_node);
        } else {
            // should never be accessed
            throw std::exception();
        }
    }

    /// @brief returns the balance of a node, taken as the height of the
    /// left child less the height of the right child. If either child is
    /// null, it's height is -1
    /// @param node
    /// @return
    int get_balance(node_pointer node) {
        int left_height = -1;
        if (node->left != nullptr) {
            left_height = node->left->height;
        }

        int right_height = -1;
        if (node->right != nullptr) {
            right_height = node->right->height;
        }

        return left_height - right_height;
    }

    /// @brief performs a right rotation at node
    /// @param node the node being rotated about
    void rotate_right(node_pointer node) {
        // assume that the left child is non-null
        node_pointer left_right_child = node->left->right;
        if (node->parent != nullptr) {
            replace_child(node->parent, node, node->left);
        } else {
            root = node->left;
            root->parent = nullptr;
        }

        set_child(node->left, 1, node);
        set_child(node, 0, left_right_child);
    }

    /// @brief performs a left rotation at node
    /// @param node the node being rotated about
    void rotate_left(node_pointer node) {
        // assume that the right child is non-null
        node_pointer right_left_child = node->right->left;
        if (node->parent != nullptr) {
            replace_child(node->parent, node, node->right);
        } else {
            root = node->right;
            root->parent = nullptr;
        }

        set_child(node->right, 0, node);
        set_child(node, 1, right_left_child);
    }

    /// @brief this method is called after a new node is added and the tree
    /// is now out of balance. It performs rotations at the unbalanced nodes.
    /// @param node the node being rebalanced.
    void rebalance(node_pointer node) {
        update_height(node);
        int node_balance = get_balance(node);
        if (node_balance == -2) {
            // right-left rotation case
            if (get_balance(node->right) == 1) {
                rotate_right(node->right);
            }
            rotate_left(node);
        } else if (node_balance == 2) {
            // left-rigth rotation case
            if (get_balance(node->left) == -1) {
                rotate_left(node->left);
            }
            rotate_right(node);
        }
    }

    int max(int a, int b) { return (a >= b) ? a : b; }

 public:
    Tree() {
        root = nullptr;
        _size = 0;
    }

    ~Tree() {
        if (root != nullptr) {
            root->~TreeNode();
        }
    }

    Tree(const Tree&) = delete;

    /// @brief adds a new node to the tree with the provided string value
    /// @param str a single character string
    void insert(value_type t) {
        _size++;
        if (root == nullptr) {
            root = new TreeNode(t);
            return;
        }

        node_pointer node = new TreeNode(t);

        node_pointer curr = root;
        // searching for a place to insert the new node
        while (curr != nullptr) {
            if (t < curr->data) {
                if (curr->left == nullptr) {
                    set_child(curr, 0, node);
                    break;
                } else {
                    curr = curr->left;
                }
            } else {
                if (curr->right == nullptr) {
                    // set right as new node
                    set_child(curr, 1, node);
                    break;
                } else {
                    curr = curr->right;
                }
            }
        }
        // rebalance the tree if necessary
        node = node->parent;
        while (node != nullptr) {
            rebalance(node);
            node = node->parent;
        }
    }

    /// @brief searches for a given string in the tree. Returns true if that
    /// string is already in the tree
    /// @param str a single character string
    /// @return
    bool search(value_type t) {
        // tree is empty
        if (root == nullptr) {
            return false;
        }

        node_pointer curr = root;
        while (curr != nullptr) {
            if (curr->data == t) {
                return true;
            } else if (t < curr->data) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return false;
    }
};
