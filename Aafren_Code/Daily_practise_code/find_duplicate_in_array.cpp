// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

int main() {
    int arr[]={1,2,3,4,3,5,6,7,8,9,7};
    int n=sizeof(arr)/sizeof(arr[0]);
    int count =0;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
        if(arr[i]==arr[j])
        {
            cout<<arr[i]<<",";
            count++;
            break;
        }
        }
    }
    cout<<endl;;
    if(count==0)
    {
        cout<<"not found";
    }
    else
    {
        cout<<"dubplicate found";
    }
    return 0;
}
