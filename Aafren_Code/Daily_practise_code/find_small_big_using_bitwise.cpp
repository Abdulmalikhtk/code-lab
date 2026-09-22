#include <iostream>

int findSmallest(int a, int b, int c) {
    int count = 0;
    while (a > 0 && b > 0 && c > 0) {
        a--;
        b--;
        c--;
        count++;
    }
    return count;
}

int findLargest(int a, int b, int c) {
    int count = 0;
    while (a > 0 || b > 0 || c > 0) {
        a--;
        b--;
        c--;
        count++;
    }
    return count;
}

int main() {
    int num1 = 12, num2 = 15, num3 = 5;
    std::cout << "The smallest number is: " << findLargest(num1, num2, num3) << std::endl;

    int num1 = 12, num2 = 15, num3 = 5;
    std::cout << "The Largest number is: " << findSmallest(num1, num2, num3) << std::endl;

    return 0;
}
