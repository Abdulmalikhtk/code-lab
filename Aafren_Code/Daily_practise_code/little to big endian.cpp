#include <cstdint>
#include <iomanip>
#include <iostream>

using namespace std;

uint32_t swapEndian(uint32_t value) {
    return ((value & 0x000000FFU) << 24) |
           ((value & 0x0000FF00U) << 8)  |
           ((value & 0x00FF0000U) >> 8)  |
           ((value & 0xFF000000U) >> 24);
}

int main() {
    uint32_t number;

    cout << "Enter a 32-bit hexadecimal number: ";
    cin >> hex >> number;

    uint32_t swappedNumber = swapEndian(number);

    cout << uppercase << setfill('0');
    cout << "Original number: 0x" << setw(8) << number << '\n';
    cout << "Swapped number : 0x" << setw(8) << swappedNumber << '\n';

    return 0;
}
