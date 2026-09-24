// Online C++ compiler to run C++ program online
#include <iostream>
#include<string>

void summofallelements()
{
    int arr[]={1,3,5,7,88,43,22};
    int n=sizeof(arr)/sizeof(arr[0]);
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=arr[i];
    }
    cout<<"sum of all elements:"<<sum<<endl;
}


int main()
{
    summofallelements();
    return 0;
}
