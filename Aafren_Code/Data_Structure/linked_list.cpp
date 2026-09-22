/*-----------------------
Linked List Features:
1. createList (insertOneByOne)
2. DeleteList
3. printList
4. InsertionAtPosition
5. DeletionAtPosition
6. GetMidElement
7. MakeMidAsAFirstElement
8. ReverseList [Added from snippet 1]
9. IsPalindrome [Added from snippet 1]
10. Merge & MergeSort [Added from snippet 1]
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

// 3. printList
void printList(Node* head)
{
    while(head!=nullptr)
    {
        cout<<head->value<<"->";
        head=head->next;
    }
    cout<<"NULL"<<endl;
}

// 2. DeleteList
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

// 1. createList (Sample setup helper)
void insertOneByOne(Node* &head)
{
    Node* one=new Node(1);
    Node* two=new Node(2);
    Node* three=new Node(3);

    one->next=two;
    two->next=three;
    three->next=nullptr;

    head=one;
}

// 5. DeletionAtPosition
void deleteAtPosition(Node* &head, int k)
{
    cout << "\n--- deleteAtPosition at index " << k << " ---" << endl;
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
    int length = 0;
    while(head != nullptr)
    {
        length++;
        head = head->next;
    }
    return length;
}

// 6. GetMidElement
Node* getMidElement(Node* head)
{
    if (head == nullptr) return nullptr;
    int l = findLength(head);
    int m = l / 2;
    Node* prev = nullptr;
    while(m--)
    {
        prev = head;
        head = head->next;
    }
    return prev; // Returns node just before the true second half
}

// 7. MakeMidAsAFirstElement
void makeMidAsFirstElement(Node* &head)
{
    cout << "\n--- makeMidAsFirstElement ---" << endl;
    if (head == nullptr || head->next == nullptr) return;

    Node* prev = getMidElement(head);
    if (prev == nullptr) return;

    Node* mid = prev->next;
    cout << "Found mid value: " << mid->value << endl;

    prev->next = mid->next;
    mid->next = head;
    head = mid;
}

// 4. InsertionAtPosition
void insertValuAtPosition(Node* &head, int newvalue, int k)
{
    cout << "\n--- insertValuAtPosition value " << newvalue << " at index " << k << " ---" << endl;
    Node* newNode=new Node(newvalue);

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

// 8. ReverseList [Imported & corrected]
Node* reverseList(Node* head)
{
    Node* prev=nullptr;
    Node* current=head;
    while(current!=nullptr)
    {
        Node* nextnode=current->next;
        current->next=prev;
        prev=current;
        current=nextnode;
    }
    return prev;
}

// 9. IsPalindrome [Imported & validated]
bool isPalindrome(Node* head)
{
    if (!head || !head->next) return true;

    Node* mid = getMidElement(head);
    Node* secondHalf = reverseList(mid->next);
    Node* firstHalf = head;

    Node* tempSecond = secondHalf; // Keep tracking for matching
    bool pali = true;

    while (tempSecond != nullptr) {
        if (firstHalf->value != tempSecond->value) {
            pali = false;
            break;
        }
        firstHalf = firstHalf->next;
        tempSecond = tempSecond->next;
    }

    // Restore list structure (Best practice)
    reverseList(secondHalf);
    return pali;
}

// 10a. Merge Helper for MergeSort [Imported]
Node* merge(Node* left, Node* right)
{
    if(!left) return right;
    if(!right) return left;

    Node* result=nullptr;
    if(left->value <= right->value)
    {
        result=left;
        result->next=merge(left->next,right);
    }
    else
    {
        result=right;
        result->next=merge(left,right->next);
    }
    return result;
}

// 10b. MergeSort [Imported]
Node* mergeSort(Node* head)
{
    if(!head || !head->next)
    {
        return head;
    }

    Node* mid = getMidElement(head);
    Node* right = mid->next;
    mid->next = nullptr;

    Node* left = mergeSort(head);
    right = mergeSort(right);

    return merge(left, right);
}

int main() {
    Node* list1 = nullptr;
    insertOneByOne(list1);

    cout << "Original List 1: ";
    printList(list1);

    // Testing Insertions
    insertValuAtPosition(list1, 99, 1);
    insertValuAtPosition(list1, 102, 2);
    cout << "After Insertions: ";
    printList(list1);

    // Testing Palindrome
    cout << "\nIs list1 palindrome? " << (isPalindrome(list1) ? "Yes" : "No") << endl;

    // Testing MergeSort
    cout << "\nSorting list1 using MergeSort..." << endl;
    list1 = mergeSort(list1);
    cout << "Sorted list1: ";
    printList(list1);

    // Creating a second sorted list to test Merge
    Node* list2 = new Node(10);
    list2->next = new Node(20);
    list2->next->next = new Node(30);

    cout << "\nList 2: ";
    printList(list2);

    cout << "Merging List 1 and List 2..." << endl;
    Node* mergedList = merge(list1, list2);
    cout << "Merged Output: ";
    printList(mergedList);

    // Clean memory cleanup
    deleteList(mergedList);

    return 0;
}
