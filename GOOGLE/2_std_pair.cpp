#include<iostream>
#include<utility>
using std::pair,std::cout,std::endl;

std::pair<int , int> getValues()
{
    return{10,20};
}

//auto tells the C++ compiler to infer the variable’s type from the value returned by getValues().

int main()
{
    int [a,b] = getValues();
    std::cout<< a << " "<<std::endl;
    // std::pair<int, int> values = getValues();
    // int a = values.first;
    // int b = values.second;

    //structured binding
    // auto [a, b] = getValues();        // copies/moves values
    // const auto [a, b] = getValues();  // read-only values

    // auto& [a, b] = existingPair;      // references; changes affect the pair
    // const auto& [a, b] = existingPair; // read-only references
}

// #include <array>

// array<int, 2> getValues()
// {
//     return {10, 20};
// }

// pair<int, string> person = {25, "Malikh"};

// cout << person.first;   // 25
// cout << person.second;  // Malikh

// In modern C++, you can unpack a pair like this:

// auto [a, b] = WithoutTemp(10, 20);

// cout << a; // 20
// cout << b; // 10
