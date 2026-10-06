#include<iostream>
#include <utility>
using std::cout,std::endl;


void WithoutTemp(int num1, int num2)
{
    num1 = num1 + num2;
    cout<<num1<<endl;
    num2 = num1 - num2;
    cout<<num2<<endl;
    num1 = num1 - num2;
    cout<<num1<<endl;

    return;
}

void fibonnaci(int num)
{
    int a = 0;
    int b = 1;
    int fib = 0;

    for(int i = 0 ; i < num ; i ++)
    {
        cout<<a<<" ";
        int fib = a + b;
        a = b;
        b = fib;
    }
}

int main()
{
    int a = 10;
    int b = 20;

    //SWAP
    cout << a <<  "  ,  " << b<<endl;
    WithoutTemp(a,b);
    cout << a << "  ,  " << b <<endl;

    // fibonnaci series - nth number , n numbers , rectangle

    int num = 10;
    fibonnaci(num);






}
