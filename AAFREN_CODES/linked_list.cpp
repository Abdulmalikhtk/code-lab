#include <iostream>
using std::cout, std::endl;

class Node
{
    public:
    Node* next;
    int value;
    // Node(int val=0)
    // {
    //     value=val;
    //     next=nullptr;
    // }
};
void printList(Node* head)
{
    while(head!=nullptr)
    {
        cout<<head->value<<"->";
        head=head->next;
    }
    cout<<"NULL"<<endl;
}

void deleteList(Node* &head)
{
    while(head!=nullptr)
    {
        Node* temp=head;
        cout<<"Deleted Node:"<<head->value<<endl;
        head=head->next;
        delete temp;

    }
    head=nullptr;

}
void insertOneByOne(Node* &head)
{
    Node* one=new Node();
    Node* two=new Node();
    Node* three=new Node();

    one->value=1;
    two->value=2;
    three->value=3;

    one->next=two;
    two->next=three;
    three->next=nullptr;

    head=one;
    printList(head);

    // deleteList(head);

    one=nullptr;
    two=nullptr;
    three=nullptr;

}
int findLength(Node* head)
{
    int length=0;
    while(head!=nullptr)
    {
        length++;
        head=head->next;
    }
    return length;
}
Node* getMidElement(Node* head)
{
    int length=findLength(head);
    int mid=length/2;

    while(mid--)
    {
        head=head->next;
    }
    return head;
}

int main()
{

    Node* head;

    insertOneByOne(head);

    printList(head);

    // deleteList(head);
    Node * mid=getMidElement(head);
    cout<<"mid value:"<<mid->value<<endl;
    head=mid;
    printList(head);

    return 0;
}
