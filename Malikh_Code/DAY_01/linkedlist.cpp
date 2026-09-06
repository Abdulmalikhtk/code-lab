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

void printNode(Node* head)
{
    while(head!=nullptr)
    {
        cout<<head->value<<"->";
        head=head->next;
    }
    cout<<"NULL_PTR"<<endl;
};

int main()
{
    Node* firstNode = new Node(10);
    Node* secondNode = new Node(20);
    Node* thirdNode = new Node(30);
    // firstNode->value=10;
    // secondNode->value=20;
    firstNode->next=secondNode;
    secondNode->next=nullptr;
    printNode(firstNode);
    // cout<<firstNode->value<<endl;
    // cout<<(*((*firstNode).next)).value<<endl;
    // cout<<firstNode->next->value<<endl;

    // Node* head = nullptr;
    // cout << head -> value;
    // if(head!=nullptr)

}


// Extras


// tkabdulmalikh@tkabdulmalikh-mac DAY_01 % g++ -std=c++17 -Wall -Wextra -g \
//     -fsanitize=address,undefined \
//     linkedlist.cpp -o linked
// ./linked
// linkedlist.cpp:29:21: runtime error: member access within null pointer of type 'Node'
// SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior linkedlist.cpp:29:21
// AddressSanitizer:DEADLYSIGNAL
// =================================================================
// ==85846==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000008 (pc 0x0001046787d0 bp 0x00016b786d70 sp 0x00016b786d10 T0)
// ==85846==The signal is caused by a READ memory access.
// ==85846==Hint: address points to the zero page.
//     #0 0x0001046787d0 in main linkedlist.cpp:29
//     #1 0x000185f5c4e0 in start+0x1b4c (dyld:arm64e+0x204e0)

// ==85846==Register values:
//  x[0] = 0x0000000000000000   x[1] = 0x0000000000000103   x[2] = 0x0000000000000103   x[3] = 0x0000000104d003c0
//  x[4] = 0x0000000063000000   x[5] = 0x0000000000000000   x[6] = 0x0000000000000000   x[7] = 0x0000000000000000
//  x[8] = 0x0000000000000000   x[9] = 0x0000000000000008  x[10] = 0x000000000000003d  x[11] = 0x0000000000000001
// x[12] = 0x0000000000000000  x[13] = 0x000000010518898c  x[14] = 0x000000016b785dd8  x[15] = 0x000000010518897e
// x[16] = 0x000000018632e8c4  x[17] = 0x00000001050e05d8  x[18] = 0x0000000000000000  x[19] = 0x00000001f2ab0058
// x[20] = 0x00000001f2ab0100  x[21] = 0x000000016b786e08  x[22] = 0xfffffffffffffff0  x[23] = 0x00000001f2d67a60
// x[24] = 0x0000000000000001  x[25] = 0x000000016b786f70  x[26] = 0x00000001f2d67a70  x[27] = 0x0000000000000000
// x[28] = 0x0000000000000000     fp = 0x000000016b786d70     lr = 0x0000000104678738     sp = 0x000000016b786d10
// AddressSanitizer can not provide additional info.
// SUMMARY: AddressSanitizer: SEGV linkedlist.cpp:29 in main
// ==85846==ABORTING
// zsh: abort      ./linked
// tkabdulmalikh@tkabdulmalikh-mac DAY_01 %

// lldb ./linked

// (lldb) run
// (lldb) backtrace
// (lldb) frame variable
