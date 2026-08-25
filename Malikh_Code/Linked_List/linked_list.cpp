// linked_list.cpp — Singly Linked List, complete reference implementation
//
// Build:  make
// Run:    make run F=linked_list
// Memory: make asan          (catches leaked nodes and use-after-free)

#include<iostream>
using std::cout,std::endl;

// ---------------------------------------------------------------------------
// The Node
// ---------------------------------------------------------------------------
// A node holds the data and the address of the next node. The `next` pointer
// is of the same type as the class itself — that self-reference is what makes
// the chain possible.
//
//   head
//    |
//    v
//   +----+---+    +----+---+    +----+------+
//   | 10 | *-+--->| 20 | *-+--->| 30 | NULL |
//   +----+---+    +----+---+    +----+------+
//
// The last node points to nullptr, which marks the end of the list.

class Node{
    public:
        int data;
        Node* next;

        // Always null `next` in the constructor. An uninitialised pointer holds
        // garbage, and traversing into it crashes.
        Node(int val){
            data = val;
            next = nullptr;
        }
};

// ---------------------------------------------------------------------------
// Traversal
// ---------------------------------------------------------------------------

// O(n). Walk from head to nullptr, printing each node.
void display(Node* head){
    Node* temp = head;
    while(temp != nullptr){
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// O(n). Count the nodes.
int length(Node* head){
    int count = 0;
    for(Node* temp = head; temp != nullptr; temp = temp->next){
        count++;
    }
    return count;
}

// ---------------------------------------------------------------------------
// Insertion
// ---------------------------------------------------------------------------

// O(1). Insert at the front.
//
// Note the parameter type: `Node*& head`, a REFERENCE to the pointer. This
// function changes where head points, so it must be by reference. Writing
// `Node* head` instead is the single most common beginner bug — the caller's
// head never updates and the list appears to stay empty.
void insertAtHead(Node*& head, int val){
    Node* newNode = new Node(val);
    newNode->next = head;   // new node points to the old first node
    head = newNode;         // new node becomes the first node
}

// O(n). Insert at the end.
void insertAtTail(Node*& head, int val){
    Node* newNode = new Node(val);

    // Empty list: there is no previous node to attach to, so the new node
    // becomes the head itself.
    if(head == nullptr){
        head = newNode;
        return;
    }

    // Walk to the LAST node. The condition is `temp->next != nullptr`, not
    // `temp != nullptr` — we need to stand ON the last node, not walk past it.
    // Using `temp != nullptr` would leave temp as nullptr and the next line
    // would crash.
    Node* temp = head;
    while(temp->next != nullptr){
        temp = temp->next;
    }

    temp->next = newNode;
}

// O(n). Insert at a 0-based position. Position 0 means the front.
void insertAtPos(Node*& head, int val, int pos){
    if(pos <= 0){
        insertAtHead(head, val);
        return;
    }

    // Stop at the node BEFORE the target position.
    Node* temp = head;
    for(int i = 0; i < pos - 1 && temp != nullptr; i++){
        temp = temp->next;
    }

    if(temp == nullptr){    // position is past the end of the list
        cout << "Position out of range" << endl;
        return;
    }

    Node* newNode = new Node(val);

    // ORDER MATTERS. Link the new node to the rest of the list FIRST, then
    // attach the previous node to it. Doing it the other way round overwrites
    // temp->next and loses everything after this point.
    newNode->next = temp->next;
    temp->next = newNode;
}

// ---------------------------------------------------------------------------
// Deletion
// ---------------------------------------------------------------------------

// O(1). Remove the first node.
void deleteAtHead(Node*& head){
    if(head == nullptr) return;

    Node* toDelete = head;
    head = head->next;      // move head forward first
    delete toDelete;        // then free the old node
}

// O(n). Remove the first node containing `val`.
void deleteValue(Node*& head, int val){
    if(head == nullptr) return;

    // Deleting the head is a special case: there is no previous node whose
    // `next` we can rewire, so we move `head` itself.
    if(head->data == val){
        deleteAtHead(head);
        return;
    }

    // Stop at the node BEFORE the one to delete. In a singly linked list you
    // cannot go backwards, so you must approach from the predecessor.
    Node* temp = head;
    while(temp->next != nullptr && temp->next->data != val){
        temp = temp->next;
    }

    if(temp->next == nullptr){      // value not found
        cout << "Value " << val << " not found" << endl;
        return;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;    // bypass the node
    delete toDelete;                // then free it — never the other way round
}

// O(n). Remove the node at a 0-based position.
void deleteAtPos(Node*& head, int pos){
    if(head == nullptr || pos < 0) return;

    if(pos == 0){
        deleteAtHead(head);
        return;
    }

    Node* temp = head;
    for(int i = 0; i < pos - 1 && temp != nullptr; i++){
        temp = temp->next;
    }

    if(temp == nullptr || temp->next == nullptr){
        cout << "Position out of range" << endl;
        return;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete;
}

// ---------------------------------------------------------------------------
// Search
// ---------------------------------------------------------------------------

// O(n). True if `key` is in the list.
bool search(Node* head, int key){
    for(Node* temp = head; temp != nullptr; temp = temp->next){
        if(temp->data == key) return true;
    }
    return false;
}

// O(n). 0-based index of `key`, or -1 if absent.
int indexOf(Node* head, int key){
    int i = 0;
    for(Node* temp = head; temp != nullptr; temp = temp->next){
        if(temp->data == key) return i;
        i++;
    }
    return -1;
}

// ---------------------------------------------------------------------------
// Classic algorithms
// ---------------------------------------------------------------------------

// O(n) time, O(1) space. Reverse the list and return the new head.
//
// Walk the list flipping each `next` pointer backwards. Three pointers are
// needed: `prev` (already flipped), `curr` (being flipped), and `nxt` (saved
// before flipping, or the rest of the list would be lost).
Node* reverse(Node* head){
    Node* prev = nullptr;
    Node* curr = head;

    while(curr != nullptr){
        Node* nxt = curr->next;     // save the rest of the list
        curr->next = prev;          // flip this link backwards
        prev = curr;                // advance both pointers
        curr = nxt;
    }

    return prev;    // prev is the last node visited = the new head
}

// O(n). Recursive reverse. Elegant, but uses O(n) stack — risky for long lists.
Node* reverseRecursive(Node* head){
    if(head == nullptr || head->next == nullptr) return head;

    Node* newHead = reverseRecursive(head->next);
    head->next->next = head;    // make the next node point back to this one
    head->next = nullptr;       // this node becomes the new tail
    return newHead;
}

// O(n) time, O(1) space. Find the middle node.
//
// Slow/fast pointers: `slow` moves one step, `fast` moves two. When `fast`
// reaches the end, `slow` is at the middle. On an even-length list this
// returns the second of the two middle nodes.
Node* middle(Node* head){
    Node* slow = head;
    Node* fast = head;

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// O(n) time, O(1) space. Floyd's Tortoise and Hare cycle detection.
//
// If the list loops, the fast pointer eventually laps the slow one and they
// meet. If there is no loop, fast simply runs off the end.
bool hasCycle(Node* head){
    Node* slow = head;
    Node* fast = head;

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }

    return false;
}

// O(n) time, O(1) space. The nth node from the end, 1-based. nullptr if n is
// larger than the list.
//
// Move `fast` n steps ahead, then advance both together. When `fast` hits the
// end, `slow` is n nodes from it.
Node* nthFromEnd(Node* head, int n){
    Node* fast = head;
    for(int i = 0; i < n; i++){
        if(fast == nullptr) return nullptr;
        fast = fast->next;
    }

    Node* slow = head;
    while(fast != nullptr){
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

// O(n + m). Merge two sorted lists into one sorted list.
//
// The dummy node is the trick here: it gives `tail` something to attach to on
// the first iteration, which removes all the special-casing for the first
// element. The real head is dummy.next.
Node* mergeSorted(Node* a, Node* b){
    Node dummy(0);
    Node* tail = &dummy;

    while(a != nullptr && b != nullptr){
        if(a->data <= b->data){
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    // One list is now empty. Attach whatever is left of the other.
    tail->next = (a != nullptr) ? a : b;

    return dummy.next;
}

// O(n). Remove consecutive duplicates from a SORTED list.
void removeDuplicatesSorted(Node* head){
    Node* temp = head;

    while(temp != nullptr && temp->next != nullptr){
        if(temp->data == temp->next->data){
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            // Do not advance — there may be three or more in a row.
        } else {
            temp = temp->next;
        }
    }
}

// ---------------------------------------------------------------------------
// Cleanup
// ---------------------------------------------------------------------------

// O(n). Free every node. Every `new` needs a matching `delete`, or the memory
// leaks. Run `make asan` to have the compiler catch it when you forget.
void destroy(Node*& head){
    while(head != nullptr){
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}

// ---------------------------------------------------------------------------
// Demo
// ---------------------------------------------------------------------------

int main(){
    Node* head = nullptr;       // an empty list is just a null head pointer

    cout << "--- Insertion ---" << endl;
    insertAtTail(head, 10);
    insertAtTail(head, 20);
    insertAtTail(head, 30);
    cout << "insertAtTail 10,20,30 : ";
    display(head);

    insertAtHead(head, 5);
    cout << "insertAtHead 5        : ";
    display(head);

    insertAtPos(head, 15, 2);
    cout << "insertAtPos 15 at 2   : ";
    display(head);

    cout << "length                : " << length(head) << endl;

    cout << endl << "--- Search ---" << endl;
    cout << "search(20)            : " << (search(head, 20) ? "found" : "not found") << endl;
    cout << "search(99)            : " << (search(head, 99) ? "found" : "not found") << endl;
    cout << "indexOf(15)           : " << indexOf(head, 15) << endl;

    cout << endl << "--- Algorithms ---" << endl;
    cout << "middle                : " << middle(head)->data << endl;
    cout << "2nd from end          : " << nthFromEnd(head, 2)->data << endl;
    cout << "hasCycle              : " << (hasCycle(head) ? "yes" : "no") << endl;

    head = reverse(head);
    cout << "reverse               : ";
    display(head);

    head = reverse(head);       // reverse back to the original order
    cout << "reverse again         : ";
    display(head);

    cout << endl << "--- Deletion ---" << endl;
    deleteValue(head, 15);
    cout << "deleteValue 15        : ";
    display(head);

    deleteAtHead(head);
    cout << "deleteAtHead          : ";
    display(head);

    deleteAtPos(head, 1);
    cout << "deleteAtPos 1         : ";
    display(head);

    cout << endl << "--- Merge two sorted lists ---" << endl;
    Node* a = nullptr;
    insertAtTail(a, 1);
    insertAtTail(a, 3);
    insertAtTail(a, 5);
    cout << "list a                : ";
    display(a);

    Node* b = nullptr;
    insertAtTail(b, 2);
    insertAtTail(b, 4);
    insertAtTail(b, 6);
    cout << "list b                : ";
    display(b);

    Node* merged = mergeSorted(a, b);
    cout << "merged                : ";
    display(merged);
    a = b = nullptr;            // both lists now live inside `merged`

    cout << endl << "--- Remove duplicates ---" << endl;
    Node* dup = nullptr;
    insertAtTail(dup, 1);
    insertAtTail(dup, 1);
    insertAtTail(dup, 2);
    insertAtTail(dup, 3);
    insertAtTail(dup, 3);
    insertAtTail(dup, 3);
    cout << "before                : ";
    display(dup);
    removeDuplicatesSorted(dup);
    cout << "after                 : ";
    display(dup);

    // Free everything. Without this the program leaks every node it allocated.
    destroy(head);
    destroy(merged);
    destroy(dup);

    return 0;
}
