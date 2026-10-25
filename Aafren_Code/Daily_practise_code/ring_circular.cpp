/** 1. Ring Buffer / Circular Buffer
A ring buffer and circular buffer are the same. When the index reaches the end, it returns to the beginning using the modulo (%) operator.

Output:

Removed: 10
Removed: 20
**/
#include <iostream>
using namespace std;

class CircularBuffer {
private:
    static const int SIZE = 5;
    int buffer[SIZE];
    int front = 0;
    int rear = 0;
    int count = 0;

public:
    bool push(int value) {
        if (count == SIZE) {
            cout << "Buffer is full\n";
            return false;
        }

        buffer[rear] = value;
        rear = (rear + 1) % SIZE;
        count++;
        return true;
    }

    bool pop(int& value) {
        if (count == 0) {
            cout << "Buffer is empty\n";
            return false;
        }

        value = buffer[front];
        front = (front + 1) % SIZE;
        count--;
        return true;
    }
};

int main() {
    CircularBuffer buffer;

    buffer.push(10);
    buffer.push(20);
    buffer.push(30);

    int value;

    if (buffer.pop(value))
        cout << "Removed: " << value << '\n';

    if (buffer.pop(value))
        cout << "Removed: " << value << '\n';

    return 0;
}
