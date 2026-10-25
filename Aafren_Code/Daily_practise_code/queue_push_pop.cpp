#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> numbers;

    numbers.push(10);
    numbers.push(20);
    numbers.push(30);

    while (!numbers.empty()) {
        cout << "Front: " << numbers.front() << '\n';
        numbers.pop();
    }

    return 0;
}
