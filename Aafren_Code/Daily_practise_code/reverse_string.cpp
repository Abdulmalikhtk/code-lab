#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str="Hellow";

    int n=str.length();
    string str1;
    cout<<"reversed string:";
    for(int i=n-1;i>=0;i--)
    {
        str1+=str[i];
        cout<<str[i];
    }
    cout<<endl;
    cout<<"New String variable value is:"<<str1<<endl;
    if(str==str1)
    {
        cout<<"string is palindrome"<<endl;
    }
    else
    {
        cout<<"string is not a palindrome"<<endl;
    }

    return 0;
}
