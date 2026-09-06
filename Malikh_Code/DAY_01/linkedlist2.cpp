#include<iostream>
using std::cout,std::endl;

class Node
{
    public:
        Node* next;
        int value;
    Node(int val = 0)
    {
        next = nullptr;
        value = val;
    };
};

void insertNode(Node*& head)
{
    head = new Node(10);
}

 void changePointer(Node* pointer)
 {
    pointer=&second;
    cout<<pointer<<endl;
 }

int main()
{
    // Node* head = nullptr;
    // insertNode(head);
    // cout<<head;

    Node first(10);
    Node second(20);
    Node* head = &first;
    cout<<head<<endl;

    changePointer(head,&second);
    count<<head->value<<endl;

}
