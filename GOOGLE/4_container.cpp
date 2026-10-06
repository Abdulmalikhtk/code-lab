#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

void vectorExample()
{
    cout << "========== VECTOR ==========\n";
    // Dynamic size, contiguous memory, duplicate values allowed.
    vector<int> numbers = {10, 20, 30};

    numbers.push_back(40);             // Add at end: usually O(1)
    numbers.emplace_back(50);          // Construct/add at end
    numbers.insert(numbers.begin() + 1, 15); // Insert: O(n)

    cout << "Elements: ";
    for (int number : numbers)
        cout << number << " ";
    cout << '\n';

    cout << "front=" << numbers.front()
         << ", back=" << numbers.back()
         << ", [2]=" << numbers[2]
         << ", at(2)=" << numbers.at(2) << '\n';
    // [] is unchecked. at() throws out_of_range for an invalid index.

    numbers[0] = 100;
    numbers.pop_back();                // Remove last: O(1)
    numbers.erase(numbers.begin() + 1); // Remove index 1: O(n)

    auto found = find(numbers.begin(), numbers.end(), 30); // O(n)
    if (found != numbers.end())
        cout << "30 found at index " << distance(numbers.begin(), found) << '\n';

    sort(numbers.begin(), numbers.end());    // O(n log n)
    reverse(numbers.begin(), numbers.end()); // O(n)
    numbers.reserve(20);              // Increase capacity, not size
    numbers.resize(6, 0);             // Change size; new values are 0

    cout << "After operations: ";
    for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
        cout << *it << " ";
    cout << "\nsize=" << numbers.size()
         << ", capacity=" << numbers.capacity()
         << ", empty=" << numbers.empty() << '\n';

    vector<int> copy = numbers;
    copy.clear();                      // Remove all elements
    cout << "Copy empty after clear: " << copy.empty() << "\n\n";
}

void arrayExample()
{
    cout << "========== ARRAY ==========\n";
    // Fixed size, contiguous memory. Size is part of its type.
    array<int, 5> values = {5, 2, 4, 1, 3};

    cout << "Elements: ";
    for (int value : values)
        cout << value << " ";
    cout << '\n';

    cout << "front=" << values.front()
         << ", back=" << values.back()
         << ", [2]=" << values[2]
         << ", at(2)=" << values.at(2) << '\n';

    values[0] = 50;
    sort(values.begin(), values.end());
    auto found = find(values.begin(), values.end(), 4); // O(n)
    if (found != values.end())
        cout << "4 found at index " << distance(values.begin(), found) << '\n';

    cout << "Sorted: ";
    for (auto it = values.cbegin(); it != values.cend(); ++it)
        cout << *it << " ";
    cout << "\nsize=" << values.size() << ", empty=" << values.empty() << '\n';

    array<int, 5> filled{};
    filled.fill(7);                    // Assign 7 to every element
    values.swap(filled);               // Exchange same-type arrays
    cout << "After fill and swap: ";
    for (int value : values)
        cout << value << " ";
    cout << "\n\n";

    // No push_back, pop_back, insert, erase, resize, or clear.
    // Index access: O(1), search: O(n), sort: O(n log n).
}

void setExample()
{
    cout << "========== SET ==========\n";
    // Unique elements stored in sorted order.
    set<int> values = {30, 10, 20, 20}; // Duplicate 20 is ignored

    auto insertion = values.insert(40); // pair<iterator, bool>
    cout << "Was 40 inserted? " << insertion.second << '\n';
    values.emplace(25);

    cout << "Sorted unique elements: ";
    for (int value : values)
        cout << value << " ";
    cout << '\n';

    auto found = values.find(20);
    if (found != values.end())
        cout << "20 found\n";
    cout << "count(20)=" << values.count(20) << '\n'; // 0 or 1

    auto lower = values.lower_bound(20); // First element >= 20
    auto upper = values.upper_bound(20); // First element > 20
    if (lower != values.end()) cout << "lower_bound(20)=" << *lower << '\n';
    if (upper != values.end()) cout << "upper_bound(20)=" << *upper << '\n';

    values.erase(10);              // Erase by value
    if (!values.empty())
        values.erase(values.begin()); // Erase by iterator

    cout << "After erase: ";
    for (auto it = values.cbegin(); it != values.cend(); ++it)
        cout << *it << " ";
    cout << "\nsize=" << values.size() << ", empty=" << values.empty() << '\n';

    set<int> copy = values;
    copy.clear();
    cout << "Copy empty after clear: " << copy.empty() << "\n\n";

    // insert, erase, find, count and bounds: normally O(log n).
    // Elements cannot be modified directly because ordering must remain valid.
}

void mapExample()
{
    cout << "========== MAP ==========\n";
    // Unique keys stored in sorted order; each key maps to one value.
    map<string, int> ages = {{"Malikh", 25}, {"Aafren", 23}};

    ages["John"] = 30;             // Insert
    ages["Malikh"] = 26;           // Update
    ages.insert({"Sara", 28});
    ages.emplace("David", 32);

    cout << "People (sorted by key):\n";
    for (const auto& [name, age] : ages) // C++17 structured binding
        cout << name << " -> " << age << '\n';

    cout << "Malikh using at(): " << ages.at("Malikh") << '\n';
    auto found = ages.find("John");
    if (found != ages.end())
        cout << "Found " << found->first << ": " << found->second << '\n';
    cout << "Does Sara exist? " << (ages.count("Sara") > 0) << '\n';

    auto firstFromM = ages.lower_bound("M");
    if (firstFromM != ages.end())
        cout << "First key from M: " << firstFromM->first << '\n';

    ages.erase("David");           // Erase by key
    if (!ages.empty())
        cout << "First sorted key: " << ages.begin()->first << '\n';
    cout << "size=" << ages.size() << ", empty=" << ages.empty() << '\n';

    map<string, int> copy = ages;
    copy.clear();
    cout << "Copy empty after clear: " << copy.empty() << "\n\n";

    // ages["Unknown"] inserts a missing key with the default int value 0.
    // ages.at("Unknown") does not insert and throws out_of_range.
    // insert, erase, find, count and bounds: normally O(log n).
}

int main()
{
    cout << boolalpha; // Display bool values as true/false
    vectorExample();
    arrayExample();
    setExample();
    mapExample();
    return 0;
}
