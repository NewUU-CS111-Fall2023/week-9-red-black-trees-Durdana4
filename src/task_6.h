#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int data) : data(data), color(BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
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

    int getBlackHeight(Node* node) {
        if (node == nullptr) {
            return 1;
        }
        int leftHeight = getBlackHeight(node->left);
        int rightHeight = getBlackHeight(node->right);
        return leftHeight + (node->color == BLACK ? 1 : 0);
    }

    void calculateAndDisplayBlackHeights(Node* node) {
        if (node != nullptr) {
            int blackHeight = getBlackHeight(node);
            cout << node->data << " - " << blackHeight << endl;
            calculateAndDisplayBlackHeights(node->left);
            calculateAndDisplayBlackHeights(node->right);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        Node* newNode = new Node(data);
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (newNode->data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        newNode->parent = parent;

        if (parent == nullptr) {
            root = newNode;
        } else if (newNode->data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        insertFixup(newNode);
    }

    void calculateAndDisplayBlackHeights() {
        calculateAndDisplayBlackHeights(root);
    }
};

int main() {
    RedBlackTree tree;

    // Sample input
    int n;
    cin >> n;
    int values[n];
    for (int i = 0; i < n; i++) {
        cin >> values[i];
        tree.insert(values[i]);
    }

    // Calculate and display the black height of every node
    tree.calculateAndDisplayBlackHeights();

    return 0;
}
