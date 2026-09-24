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

            // to remove duplicate from array use this below loop
        //     for(int k=j;k<n-1;k++)  // shift everything left by one
        //         {
        //             arr[k]=arr[k+1];
        //         }
        //         n--;                    // list is now one shorter
        //         j--;                    // recheck this index
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

    // to remove duplicate from array use this below loop
    // cout<<"after removing duplicates: ";
    // for(int i=0;i<n;i++)
    // {
    //     cout<<arr[i]<<",";
    // }
    // cout<<endl;

    return 0;
}
