#include <iostream>
#include <vector>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insertFixup(Node* node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void insertHelper(Node* node) {
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (node->data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        node->parent = parent;

        if (parent == nullptr) {
            root = node;
        } else if (node->data < parent->data) {
            parent->left = node;
        } else {
            parent->right = node;
        }

        insertFixup(node);
    }

    void printTreeHelper(Node* node) {
        if (node != nullptr) {
            std::cout << "(" << node->data << "(" << (node->color == RED ? "RED" : "BLACK") << ")";
            printTreeHelper(node->left);
            printTreeHelper(node->right);
            std::cout << ")";
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        Node* node = new Node(data);
        insertHelper(node);
    }

    void printTree() {
        printTreeHelper(root);
    }
};

int main() {
    RedBlackTree tree;

    // Sample input
    int n;
    std::cin >> n;
    std::vector<int> values(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i];
        tree.insert(values[i]);
    }

    // Print the tree
    tree.printTree();

    return 0;
}
