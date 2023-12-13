/*
 * Author:
 * Date:
 * Name:
 */
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

        // Make the root black
        if (node->parent == nullptr) {
            node->color = BLACK;
        } else {
            node->color = RED;
        }
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
