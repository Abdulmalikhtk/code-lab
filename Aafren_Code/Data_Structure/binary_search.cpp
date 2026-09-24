#include <iostream>
// #include <algorithm>
using namespace std;

int binarysearchList(int arr[],int target, int n)
{
    int left=0;
    int right=n-1;

    while(left<=right)
    {
        int mid=left+(right-left)/2;
        if(arr[mid]==target)
        {
            return mid;
        }
        else if(arr[mid]<target)
        {
        left=mid+1;
        }
        else
        {
        right=mid-1;
        }
    }
    return -1;
}
void sortList(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>=arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    // return arr[];
}
int main()
{
    int arr[]={1,5,6,7,22,2,4,15,55,3};
    // int arr[]={1,2,5,8,9,22,55,66,99};

    int target=55;
    int n=sizeof(arr)/sizeof(arr[0]);
    sortList(arr,n);
    cout<<"sorted arr:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }

    int result=binarysearchList(arr,target,n);

    if(result==-1)
    {
    cout<<"not found";
    }
    else
    {
        cout<<"element founded at the index of "<<result;
    }
    return 0;
}
