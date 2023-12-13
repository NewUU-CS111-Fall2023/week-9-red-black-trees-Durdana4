#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insertHelper(root, data);
    }

    Node* insertHelper(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data < node->data) {
            node->left = insertHelper(node->left, data);
        } else if (data > node->data) {
            node->right = insertHelper(node->right, data);
        }

        return node;
    }

    int getNumChildren(int data) {
        Node* node = search(data);
        if (node != nullptr) {
            return countChildren(node);
        }
        return 0;
    }

    int countChildren(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return countChildren(node->left) + countChildren(node->right) + 1;
    }

    Node* search(int data) {
        return searchHelper(root, data);
    }

    Node* searchHelper(Node* node, int data) {
        if (node == nullptr || node->data == data) {
            return node;
        }

        if (data < node->data) {
            return searchHelper(node->left, data);
        }

        return searchHelper(node->right, data);
    }

    void printChildrenCounts() {
        printChildrenCountsHelper(root);
    }

    void printChildrenCountsHelper(Node* node) {
        if (node != nullptr) {
            printChildrenCountsHelper(node->left);
            cout << node->data << " - " << countChildren(node) - 1 << endl;
            printChildrenCountsHelper(node->right);
        }
    }
};

int main() {
    BinaryTree tree;

    // Input
    int numValues;
    cin >> numValues;
    for (int i = 0; i < numValues; i++) {
        int value;
        cin >> value;
        tree.insert(value);
    }

    // Display the number of children for each node
    tree.printChildrenCounts();

    return 0;
}
