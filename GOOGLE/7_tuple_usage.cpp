#include<iostream>
#include<tuple>
using std::cout,std::endl,std::tie;


std::tuple<int, int> swap(int a, int b)
{
    return {b,a};
}


int main()
{
    int a = 10;
    int b = 20;
    std::tie(a,b) = swap(a,b);
    cout<<a<<" "<<b<<endl;
}
