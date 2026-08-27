// int x; variable holding an int
// int* p; variable holding the address of an int

// Node* next; does not store a Node. It stores where a Node lives in memory — an address, a number.

// Class Node{
//     public:
//         int data; // the value:   10
//         Node* next;  // an address:  0x600000004050
//         if
//         Node next; //. // ERROR: field has incomplete type 'Node'
//         The compiler rejects this, and the reason is size. To create a Node it must know how many bytes one occupies. But a Node would contain a Node, which contains a Node... infinitely. The size can never be computed.

//         A pointer is always the same size — 8 bytes on your Mac — regardless of what it points to. The compiler knows that immediately, so the class is well-defined.

//     Real numbers from your machine:

//     sizeof(int)   = 4 bytes
//     sizeof(Node*) = 8 bytes
//     sizeof(Node)  = 16 bytes     (4 + 8 = 12, padded to 16 for alignment)

//     Every node is 16 bytes no matter how long the list is.

//     The address is the link
//         0x1000                0x2000                0x3000
//        +--------+            +--------+            +--------+
// head → | data 10|      ┌───→ | data 20|      ┌───→ | data 30|
// 0x1000 | next   |──────┘     | next   |──────┘     | next   |→ nullptr
//        | 0x2000 |            | 0x3000 |            |   0    |
//        +--------+            +--------+            +--------+

// };

// The nodes are scattered anywhere in memory — 0x1000, 0x2000, 0x3000 could be far apart. There's no array, no contiguity. The only thing holding the list together is each node storing the address of the next one.

// That's also why access is O(n): to reach node 3 you must read node 1 to learn where node 2 is, read node 2 to learn where node 3 is. There's no formula to jump straight there.

// nullptr means "the chain stops here"
// nullptr is address zero — a value guaranteed never to be a real object. When traversal reads next and finds nullptr, that's the end signal:

// while(temp != nullptr){    // "while there is still a node"
//     temp = temp->next;
// }

// #include<iostream>
// using std::cout,std::endl;
// int main(){
//     cout<<"hello world Abdul";
// }
#include<iostream>
using std::cout,std::endl;

// class Node{
//    public:
//         int value;
//         Node* node;
//    Node(int val=0)
//    {
//     value=val;
//     node = nullptr;
//    }

// };



int main(){

    //creating linked list

    Node first(10);//object initiation
    Node second(20);
    cout<<second.value<<endl;
    cout<<first.value<<endl;
    first.node = &second;
    second.node = nullptr;
    cout<<second.node<<endl;
    cout<<first.node<<endl;
    // int value = 10;
    // int* val = &value; // A pointer can store only an address
    //cout<<value<<endl;
    // cout<<sizeof(val)<<endl; //pointer size
    // cout<<sizeof(*val)<<endl; //// pointed-to value size
    //64-bit - pointer size 8 bytes
    //32-bit - pointer size 4 bytes
    Node third(10);
    Node* pointer=&first;
    cout << pointer <<endl;
    cout << pointer -> value <<endl;

    int datas = 10;
    int* val = &datas ;
    cout << val <<endl;
    int data = *val;
    cout << data << endl;

}

//class Node - creates a new type called node similar to how int is a type
//public - everything bellow it can be accessed outside the class

//constructor with member initializer list

//Node(int val = 0) : value(val), node(nullptr) {}

// Node(int val = 0) — constructor; val defaults to 0
// value(val) — initializes value with val
// node(nullptr) — initializes the pointer
// {} — empty constructor body
// Both now work:

// Node first;      // value = 0
// Node second{10}; // value = 10
// “Constructor initialization” is the usual term
