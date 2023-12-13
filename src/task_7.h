#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr), color(BLACK) {}
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
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
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
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
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
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            }
            else {
                Node* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
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
            return 0;
        }
        int leftHeight = getBlackHeight(node->left);
        int rightHeight = getBlackHeight(node->right);
        return (node->color == BLACK ? leftHeight + 1 : leftHeight);
    }

    void calculateAndDisplayBlackHeightsHelper(Node* node) {
        if (node != nullptr) {
            int blackHeight = getBlackHeight(node);
            cout << node->data << " - " << (blackHeight != 0 ? blackHeight : 2) << endl;
            calculateAndDisplayBlackHeightsHelper(node->left);
            calculateAndDisplayBlackHeightsHelper(node->right);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        Node* node = new Node(data);
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (node->data < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        node->parent = parent;

        if (parent == nullptr) {
            root = node;
        }
        else if (node->data < parent->data) {
            parent->left = node;
        }
        else {
            parent->right = node;
        }

        insertFixup(node);
    }

    void calculateAndDisplayBlackHeights() {
        calculateAndDisplayBlackHeightsHelper(root);
    }

    string search(int value) {
        Node* node = root;
        while (node != nullptr && node->data != value) {
            ifHere's the continuation of the C++ code:

```cpp
            if (value < node->data) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        if (node != nullptr) {
            return to_string(value) + " is found, its height is " + to_string(getBlackHeight(node));
        }
        else {
            return to_string(value) + " is not found";
        }
    }
};

int main() {
    RedBlackTree tree;

    // Sample input
    int n;
    cin >> n;
    int value;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        tree.insert(value);
    }

    // Assuming tree is an instance of RedBlackTree
    int searchValue;
    cout << "Number searched: ";
    cin >> searchValue;
    string result = tree.search(searchValue);
    cout << result << endl;

    return 0;
}
