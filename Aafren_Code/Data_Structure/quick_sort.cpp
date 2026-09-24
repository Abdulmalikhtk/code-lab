#include <iostream>

using namespace std;

class Sort
{
    public:
    int findpivot(int arr[],int l,int r)
    {
     int pivot=arr[r];
     int i=l-1;

     for(int j=l;j<r;j++)
     {
         if(arr[j]<pivot)
         {
             i++;

             int temp=arr[i];
             arr[i]=arr[j];
             arr[j]=temp;
         }
     }

     int temp=arr[i+1];
     arr[i+1]=arr[r];
     arr[r]=temp;

     return i+1;
    }
    void quickSort(int arr[],int l,int r)
    {
        if(l<r)
        {
            int pi=findpivot(arr,l,r);
            quickSort(arr,l,pi-1);
            quickSort(arr,pi+1,r);
        }
    }
};
int main()
{
    int arr[]={1,6,8,32,46,79,43,22,45,67,89};
    int n=sizeof(arr)/sizeof(arr[0]);
    Sort s;
    s.quickSort(arr,0,n-1);
    cout<<"Sorted Array Using quick sort method"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
