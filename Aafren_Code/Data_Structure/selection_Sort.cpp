#include <iostream>

 using namespace std;

 void swap(int *a,int *b)
 {
     int temp=*a;
     *a=*b;
     *b=temp;
 }
 void selectionSort(int arr[],int n)
 {
     for(int i=0;i<n-1;i++)
     {
     int minimun_index=i;
     for(int j=i+1;j<n;j++)
     {
       if(arr[j]<arr[minimun_index])
       {
           swap(arr[j],arr[minimun_index]);
       }
     }
     }

 }
 int main()
 {
     int arr[]={1,3,6,2,5,98,73,90};
     int n=sizeof(arr)/sizeof(arr[0]);
     selectionSort(arr,n);

     for(int i=0;i<n;i++)
     {
         cout<<arr[i]<<" ";
     }
 }
