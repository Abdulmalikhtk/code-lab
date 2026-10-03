#include <iostream>
#include <vector>
#include <unordered_map> // For std::unordered_map

void findDuplicatesHashMap(const std::vector<int>& arr) {
    std::unordered_map<int, int> freqMap;
    for (int num : arr) {
        freqMap[num]++;
    }

    std::cout << "Duplicate elements (using hash map): ";
    for (const auto& pair : freqMap) {
        if (pair.second > 1) {
            std::cout << pair.first << " ";
        }
    }
    std::cout << std::endl;
}
