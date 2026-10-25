/**
Output:

Raw pointer value: 100
Smart pointer value: 200
**/
#include <iostream>
#include <memory>

using namespace std;

int main() {
    // Raw pointer: memory must be released manually.
    int* rawPointer = new int(100);

    cout << "Raw pointer value: " << *rawPointer << '\n';

    delete rawPointer;
    rawPointer = nullptr;

    // Smart pointer: memory is released automatically.
    unique_ptr<int> smartPointer = make_unique<int>(200);

    cout << "Smart pointer value: " << *smartPointer << '\n';

    // No delete is required for smartPointer.
    return 0;
}
