#include <iostream>

class Node
{
public:
    int value;
    Node* next;

    Node(int val)
    {
        value = val;
        next = nullptr;
    }
};

// void changePointer(Node*& pointer, Node* newAddress)
// {
//     // pointer is another name for the original head pointer.
//     pointer = newAddress;
// }

// int main()
// {
//     Node first(10);
//     Node second(20);

//     Node* head = &first;

//     std::cout << "Initially: " << head->value << '\n'; // 10

//     // 'reference' is another name for 'head'.
//     Node*& reference = head;

//     reference = &second;

//     // Changing reference changed head.
//     std::cout << "After reference assignment: "
//               << head->value << '\n'; // 20

//     // Make head point to first again.
//     head = &first;

//     changePointer(head, &second);

//     std::cout << "After function call: "
//               << head->value << '\n'; // 20

//     return 0;
// }
