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

    // auto [a, b] = getValues();        // copies/moves values
    // const auto [a, b] = getValues();  // read-only values

    // auto& [a, b] = existingPair;      // references; changes affect the pair
    // const auto& [a, b] = existingPair; // read-only references
}
