// Online C++ compiler to run C++ program online
#include <iostream>
#include<string>

void fibbonacci_number()
{
    int n=10;
    int a=0;
    int b=1;
    int result=0;
    while(true)
    {
        result=a+b;
        if(result>=n)
        {
            break;

        }
        a=b;
        b=result;
        cout<<"Fibbonacci of "<<n<<" is:"<<result<<endl;
    }

}

int main()
{
    fibbonacci_number();
    return 0;
}
