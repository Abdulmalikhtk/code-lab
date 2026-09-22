/*-----------------------
Binary Search Tree Features:
1. insert (insertValue)
2. clearTree (deleteTree)
3. Traversals: inorder, preorder, postorder
4. LeftView [Imported & Corrected from snippet 1]
5. Height estimation
6. Binary Search (search)
7. Explicit Subtree Prints [Imported from snippet 1]
----------------------------*/

#include <iostream>
#include <algorithm> // For std::max
using std::cout, std::endl, std::max;

class Node
{
    public:
    int value;
    Node* left;
    Node* right;

    Node(int val)
    {
        value = val;
        left = right = nullptr;
    }
};

// 1. Insert a value into the BST
Node* insertValue(Node* root, int val)
{
    if(root == nullptr)
        return new Node(val);
    if(val < root->value)
        root->left = insertValue(root->left, val);
    else
        root->right = insertValue(root->right, val);
    return root;
}

// 3a. Inorder Traversal (Left, Root, Right)
void inorder(Node* root)
{
    if(root == nullptr)
        return;
    inorder(root->left);
    cout << root->value << " ";
    inorder(root->right);
}

// 3b. Preorder Traversal (Root, Left, Right)
void preorder(Node* root)
{
    if(root == nullptr)
        return;
    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}

// 3c. Postorder Traversal (Left, Right, Root)
void postorder(Node* root)
{
    if(root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->value << " ";
}

// 4. Correct Left View Implementation
// (Prints the first node encountered at each depth level)
void leftViewUtil(Node* root, int level, int &maxLevel)
{
    if (root == nullptr)
        return;

    // If this is the first node of its depth level
    if (maxLevel < level) {
        cout << root->value << " ";
        maxLevel = level;
    }

    // Recur for left subtree first, then right subtree
    leftViewUtil(root->left, level + 1, maxLevel);
    leftViewUtil(root->right, level + 1, maxLevel);
}

void leftView(Node* root)
{
    int maxLevel = 0;
    leftViewUtil(root, 1, maxLevel);
    cout << endl;
}

// 5. Find Height of the Tree
int height(Node* root)
{
    if(root == nullptr)
        return 0;
    int leftTreeHeight = height(root->left);
    int rightTreeHeight = height(root->right);
    return max(leftTreeHeight, rightTreeHeight) + 1;
}

// 6. Search for a key in the BST
bool search(Node* root, int key)
{
    if(root == nullptr)
        return false;
    if(root->value == key)
        return true;
    else if(key < root->value)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// 2. Clear Tree (Safely cleaning up allocated heap memory to prevent leaks)
void clearTree(Node* root)
{
    if(root == nullptr)
        return;
    clearTree(root->left);
    clearTree(root->right);
    cout << "Deleted value: " << root->value << endl;
    delete root;
}

int main() {
    Node* root = nullptr;

    // Testing initial inserts (Using values from Snippet 1 to show balanced testing)
    root = insertValue(root, 5);
    root = insertValue(root, 2);
    root = insertValue(root, 6);

    cout << "preOrderTree: ";
    preorder(root);
    cout << endl;

    cout << "inOrderTree: ";
    inorder(root);
    cout << endl;

    cout << "postOrderTree: ";
    postorder(root);
    cout << endl;

    // Inserting more values
    root = insertValue(root, 4);
    root = insertValue(root, 7);
    root = insertValue(root, 9);

    cout << "\ninOrderTree after more insertions: ";
    inorder(root);
    cout << endl;

    // Testing Left View
    cout << "Left View of Tree: ";
    leftView(root);

    // Testing Height
    cout << "Height of the tree: " << height(root) << endl;

    // Testing Search feature
    int key = 7;
    if(search(root, key)) {
        cout << key << " found in tree" << endl;
    } else {
        cout << key << " not found in tree" << endl;
    }

    // 7. Explicit Subtree Prints (Imported and protected against empty cases)
    if(root) {
        cout << "\nLeft subtree of root (inorder): " << root->value << " ";
        inorder(root->left);
        cout << endl;

        cout << "Right subtree of root (inorder): " << root->value << " ";
        inorder(root->right);
        cout << endl;
    }

    // Complete tree cleanup
    cout << "\nCleaning up tree memory..." << endl;
    clearTree(root);
    root = nullptr;

    return 0;
}
