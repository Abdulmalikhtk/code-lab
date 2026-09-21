// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

void reversearray(int arr[],int n)
{
    cout<<"Actual Array values: ";
    for(int i=0;i<n;++i)
    {
    cout<<arr[i]<<" ";
    }
    cout<<endl;

    int left=0;
    int right=n-1;
    while(left<right)
    {
        int temp=arr[left];
        arr[left]=arr[right];
        arr[right]=temp;
        right--;
        left++;
    }
    cout<<"Reveersed Array: ";
    for(int i=0;i<n;++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

string reversestring(string str,int n)
{

    int left=0;
    int right=n-1;
    while(left<right)
    {
        int temp=str[left];
        str[left]=str[right];
        str[right]=temp;
        right--;
        left++;
    }
    cout<<"Reveersed String: ";
    for(int i=0;i<n;++i)
    {
        cout<<str[i];
    }
    cout<<endl;
    return str;
}

int main() {
    int arr[]={1,2,5,33,22,7,33,55,1,100};
    int n=sizeof(arr)/sizeof(arr[0]);
    reversearray(arr,n);
    cout<<"reversed array simple logic:";
    for(int i=n-1;i>=0;--i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    string str="madam";
    int n1=str.length();
    string str1=reversestring(str,n1);
    cout<<"reversed string simple logic:";
    for(int i=n1;i>=0;--i)
    {
        cout<<str1[i];
    }
    cout<<endl;
    if(str==str1)
    {
        cout<<"palidrome"<<endl;
    }
    else
    {
        cout<<"not palidrome"<<endl;
    }
     cout<<endl;

    int number=121;
    int actualnumber=number;
    reversenumber(number);
    int remiander;
    int rev=0;

    while(number>0)
    {
        remiander=number%10;
        rev=remiander+(rev*10);
        number=number/10;
    }
    cout<<"reveerse Number"<<rev<<endl;

    if(actualnumber==rev)
    {
        cout<<"Number is palidrome"<<endl;
    }
    else
    {
        cout<<"Number is not palidrome"<<endl;
    }

    return 0;
}
