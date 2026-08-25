/*-----------------------

Linked List:
1. createList (Sasken)
2. DeleteList
3. printList
4. InsertionAtPosition
5. DeletionAtPosition
6. GetMidElement (Sasken)
7. MakeMidAsAFirstElement.

----------------------------*/

#include <iostream>
using std::cout, std::endl;

class Node
{
    public:
    Node* next;
    int value;
    Node(int val=0)
    {
        value=val;
        next=nullptr;
    }
};

void printList(Node* head)
{
    cout << "\n--- printList ---" << endl;
    while(head!=nullptr)
    {
        cout<<head->value<<"->";
        head=head->next;
    }
    cout<<"NULL"<<endl;
}

void deleteList(Node* &head)
{
    cout << "\n--- deleteList ---" << endl;
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
    cout << "\n--- insertOneByOne ---" << endl;
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
}

void deleteAtPosition(Node* &head, int k)
{
    cout << "\n--- deleteAtPositio at index " << k << " ---" << endl;
    if(head==nullptr)
    {
        cout<<"List already empty"<<endl;
        return;
    }

    if(k==0)
    {
        Node* temp=head;
        head=head->next;
        cout<<"Deleted Node at position:"<<temp->value<<endl;
        delete temp;
        return;
    }

    Node* currentNode=head;

    for(int i=0;i<k-1&&currentNode!=nullptr;i++)
    {
        currentNode=currentNode->next;
    }
    if(currentNode==nullptr|| currentNode->next==nullptr)
    {
        cout<<"Out of range"<<endl;
        return;
    }
    Node* temp=currentNode->next;
    currentNode->next=temp->next;

    cout<<"Deleted Node At position:"<<temp->value<<endl;

    delete temp;
}

int findLength(Node* head)
{
    cout << "\n--- findLength ---" << endl;
    int length = 0;
    while(head != nullptr)
    {
        length++;
        head = head->next;
    }
    return length;
}

void makeMidAsFirstElement(Node* &head)
{
    cout << "\n--- makeMidAsFirstElement ---" << endl;
    if (head == nullptr || head->next == nullptr) return;

    int length = findLength(head);
    int prevIndex = (length / 2) - 1;

    Node* prev = head;
    while (prevIndex--) {
        prev = prev->next;
    }

    Node* mid = prev->next;
    cout << "Found mid value: " << mid->value << endl;

    prev->next = mid->next;
    mid->next = head;
    head = mid;
}

void insertValuAtPosition(Node* &head, int newvalue, int k)
{
    cout << "\n--- insertValuAtPosition value " << newvalue << " at index " << k << " ---" << endl;
    Node* newNode=new Node();
    newNode->value=newvalue;

    if(k==0)
    {
        newNode->next=head;
        head=newNode;
        return;
    }
    Node* currentNode=head;

    for(int i=0;i<k-1&&currentNode!=nullptr;i++)
    {
        currentNode=currentNode->next;
    }

    if(currentNode==nullptr)
    {
        cout<<"out of range"<<endl;
        delete newNode;
        return;
    }
    newNode->next=currentNode->next;
    currentNode->next=newNode;
}

int main()
{
    Node* head = nullptr;

    insertOneByOne(head);
    printList(head);

    insertValuAtPosition(head, 101, 2);
    printList(head);

    makeMidAsFirstElement(head);
    printList(head);

    deleteAtPosition(head, 2);
    printList(head);

    deleteList(head);

    return 0;
}
