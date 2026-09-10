#include <iostream>
using namespace std;

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

void inorder(Node* root)
{
    if(root == nullptr)
        return;
    inorder(root->left);
    cout << root->value << " ";
    inorder(root->right);
}

void preorder(Node* root)
{
    if(root == nullptr)
        return;
    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root)
{
    if(root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->value << " ";
}

Node* insert(Node* root, int val)
{
    if(root == nullptr)
        return new Node(val);
    if(val < root->value)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

int height(Node* root)
{
    if(root == nullptr)
        return 0;
    int leftTreeheight = height(root->left);
    int rightTreeheight = height(root->right);
    return max(leftTreeheight, rightTreeheight) + 1;
}

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

// FIX: Added function to prevent memory leaks
void clearTree(Node* root) {
    if (root == nullptr) return;
    clearTree(root->left);   // Delete left child
    clearTree(root->right);  // Delete right child
    delete root;             // Delete parent node
}

int main() {
    Node* root = nullptr;

    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);

    cout << "Inorder tree: ";
    inorder(root);
    cout << endl;

    cout << "Preorder tree: ";
    preorder(root);
    cout << endl;

    cout << "Postorder tree: ";
    postorder(root);
    cout << endl;

    root = insert(root, 4);
    root = insert(root, 5);

    cout << "Height of tree: " << height(root) << endl;

    cout << "Inorder tree: ";
    inorder(root);
    cout << endl;

    int key = 6;
    if(search(root, key))
    {
        cout << key << " found in tree" << endl; // FIXED TYPO HERE
    }
    else
    {
        cout << key << " not found in tree" << endl;
    }

    // FIX: Safely cleaning up allocated heap memory before main ends
    clearTree(root);
    root = nullptr;

    return 0;
}
