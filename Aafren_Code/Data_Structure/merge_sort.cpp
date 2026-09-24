#include <iostream>
using namespace std;

class Sort
{
    public:
void merge(int arr[],int l,int m,int r)
{
    int size1=m-l+1;
    int size2=r-m;

    int* L=new int[size1];
    int* R=new int[size2];
    // int L[100];
    // int R[100];

    for(int i=0;i<size1;i++)
    {
        L[i]=arr[l+i];
    }
    for(int j=0;j<size2;j++)
    {
        R[j]=arr[m+1+j];
    }

    int i=0,j=0,k=l;

    while(i<size1 && j<size2)
    {
     if(L[i]<=R[j])
     {
         arr[k]=L[i];
         i++;
     }
     else
     {
      arr[k]=R[j];
         j++;
     }
     k++;
    }

    while(i<size1)
    {
     arr[k]=L[i];
        i++;
        k++;
    }

    while(j<size2)
    {
        arr[k]=R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[],int l,int r)
{
if(l<r)
{
    int m=l+(r-l)/2;

    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);

    merge(arr,l,m,r);
}
}
};

int main()
{
    int arr[]={1,6,8,32,46,79,43,22,45,67,89};
    int n=sizeof(arr)/sizeof(arr[0]);
    Sort s;
    s.mergeSort(arr,0,n-1);
    cout<<"Sorted Array Using Merge sort method"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
