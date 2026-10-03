#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> a = {1, 2, 3, 4};
    vector<int> b = {5, 6, 7, 8};
    
    // Merge arrays
    vector<int> result;
    result.reserve(a.size() + b.size()); // Optimize memory allocation
    
    result.insert(result.end(), a.begin(), a.end());
    result.insert(result.end(), b.begin(), b.end());
    
    // Print result
    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i != result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    
    return 0;
}
