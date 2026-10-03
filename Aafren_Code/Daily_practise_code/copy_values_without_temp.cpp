#include <iostream>
using namespace std;

int main()
{
    int a=3;
    int b=5;
    cout<<"a: "<<a<<" b: "<<b<<endl;
    int temp;
    temp=a;
    a=b;
    b=temp;
    cout<<"a: "<<a<<" b: "<<b<<endl;
    a=a+b;
    b=a-b;
    a=a-b;
    cout<<"a: "<<a<<" b: "<<b<<endl;
    return 0;
}
