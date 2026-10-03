#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

void findDuplicatesSorted(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end()); // Sort the vector

    std::cout << "Duplicate elements (using sorting): ";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0 && arr[i] == arr[i-1]) {
            std::cout << arr[i] << " ";
            // Optional: To print each duplicate only once, add a check
            // if (i == 0 || arr[i] != arr[i-2]) { std::cout << arr[i] << " "; }
        }
    }
    std::cout << std::endl;
}
