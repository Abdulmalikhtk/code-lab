#include <iostream>
using namespace std;
int search(int arr[],int k,int n)
{
    for(int i=0;i<n;i++)
    {
        if(arr[i]==k)
        {
            // cout<<i;
        return i;
        }
    }
    return -1;
}
int main()
{
    int arr[]={1,3,5,7,9};
    int x=3;
    int n=sizeof(arr)/sizeof(arr[0]);
    int result=search(arr,x,n);
    if(result==-1)
    {
        cout<<"not there"<<endl;
    }
    else
    {
        cout<<"there at index: "<<result;
    }
    return 0;
}
