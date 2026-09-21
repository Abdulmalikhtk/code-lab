#include <iostream>
using namespace std;

int main()
{
    int arr[]={1,2,3,5,67,8,9};
    int sum=0;
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++)
    {
        sum+=arr[i];
    }
    // cout<<sum;
   int max=arr[0];
   int min=arr[0];
   for(int i=0;i<n;i++)
   {
           if(arr[i]>max)
           {
               max=arr[i];
           }
           if(arr[i]<min)
           {
               min=arr[i];
           }
   }
   cout<<max;
   cout<<min;
    return 0;
}
