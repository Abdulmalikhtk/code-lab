// Online C++ compiler to run C++ program online
#include <iostream>
#include<string>

void lamdaFunction()
{
    auto add=[](int a,int b)
    {
      return a+b;
    };
    cout<<"A+b is"<<add(4,7)<<endl;
}

void callbackFunction(int x,void (*testfuntion)(int))
{
    cout<<"before callback X value is:"<<x<<endl;
    x=x+90;
    testfuntion(x);
}
void testfuntion(int x)
{
     cout<<"After callback X value is:"<<x<<endl;
}

int main()
{
    lamdaFunction();
    callbackFunction(6,testfuntion);
    return 0;
}
