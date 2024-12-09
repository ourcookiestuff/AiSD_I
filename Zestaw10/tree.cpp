/*Jakub Dziurka, 23.12.2023 jakub.dziurka@student.uj.edu.pl

 --> Instrukcja kompilacji:
    make run
*/
#include <iostream>
#include <queue>

// Definicja struktury TreeNode
struct BSTNode {
    int value;
    BSTNode *left, *right;
    BSTNode(int x) : value(x), left(nullptr), right(nullptr) {}
};

// Funkcja rekurencyjna do zliczania liści
int calc_leafs_recursive(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    return calc_leafs_recursive(root->left) + calc_leafs_recursive(root->right);
}

// Funkcja iteracyjna do zliczania liści
int calc_leafs_iterative(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }

    std::queue<BSTNode*> nodeQueue;
    nodeQueue.push(root);
    int leaf_count = 0;

    while (!nodeQueue.empty()) {
        BSTNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (node->left == nullptr && node->right == nullptr) {
            ++leaf_count;
        } else {
            if (node->left != nullptr) {
                nodeQueue.push(node->left);
            }
            if (node->right != nullptr) {
                nodeQueue.push(node->right);
            }
        }
    }
    return leaf_count;
}

// Klasa BinaryTree
class BinaryTree {
public:
    BSTNode* root;

    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        if (!root) {
            root = new BSTNode(value);
            return;
        }
        insertNode(root, value);
    }

    void testCalcLeafs() {
        std::cout << "Liczba liści (rekurencyjnie): " << calc_leafs_recursive(root) << std::endl;
        std::cout << "Liczba liści (iteracyjnie): " << calc_leafs_iterative(root) << std::endl;
    }

    ~BinaryTree() {
        clear(root);
    }

    void clear(BSTNode* node) {
        if (node != nullptr) {
            clear(node->left);
            delete node;
        }
    }

private:
    void insertNode(BSTNode* node, int value) {
        if (value < node->value) {
            if (node->left) {
                insertNode(node->left, value);
            } else {
                node->left = new BSTNode(value);
            }
        } else {
            if (node->right) {
                insertNode(node->right, value);
            } else {
                node->right = new BSTNode(value);
            }
        }
    }
};

int main() {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    tree.testCalcLeafs();

    return 0;
}
