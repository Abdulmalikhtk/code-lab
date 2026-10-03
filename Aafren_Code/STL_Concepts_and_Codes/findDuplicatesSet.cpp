#include <iostream>
#include <vector>
#include <set> // For std::set

void findDuplicatesSet(const std::vector<int>& arr) {
    std::set<int> uniqueElements;
    std::set<int> duplicates;

    for (int num : arr) {
        if (!uniqueElements.insert(num).second) { // If insertion fails, it's a duplicate
            duplicates.insert(num);
        }
    }

    std::cout << "Duplicate elements (using set): ";
    for (int dup : duplicates) {
        std::cout << dup << " ";
    }
    std::cout << std::endl;
}
