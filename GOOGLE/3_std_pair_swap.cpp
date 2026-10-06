#include<iostream>
#include<utility>
using std::pair,std::cout,std::endl,std::tie;

pair<int , int> swapping(int a, int b)
{
    a = a + b;
    b = a - b;
    a = a - b;
    return { a , b};
}

//Yes. std::tie() is a built-in C++ Standard Library function from the <tuple> header.
int main()
{
    int a = 10;
    int b = 20;

    tie(a,b) = swapping(a,b);
    cout<<a<<" "<<b<<endl;
}
