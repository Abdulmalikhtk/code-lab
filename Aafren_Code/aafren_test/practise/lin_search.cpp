#include <iostream>

using namespace std;


int linearSearch(int arr[],int n,int k)
{
	for(int i=0;i<n;i++)
	{
		if(arr[i]==k)
		{
			return i;
		}
	}
	return -1;
}
void sorting(int arr[],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(arr[i]<arr[j])
			{
				int temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
int binaryearch(int arr[],int n,int k)
{
	sorting(arr,n);
	cout<<"After sorting array:";
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	int l=0;
	int r=n-1;
	while(l<=r)
	{
	int mid=l+(r-l)/2;
	if(arr[mid]==k)
	{
		return mid;
	}
	if(arr[mid]<k)
	{
		l=mid+1;

	}	
	else
	{
		r=mid-1;
	}
	}
	return -1;

}
int  main()
{
	int arr[]={1,442,4,6,7,88,9,6,54};
	int n=sizeof(arr)/sizeof(arr[0]);
	cout<<"Array length: "<<n<<endl;
	int k=4;
	int input;
	cout<<"Enter choice to perform which search\n 1.Linear Search \n 2.binary Search "<<endl;
	cin>>input;
	int found;
	if(input==1)
	{
	found=linearSearch(arr,n,k);
	}
	else
	{
	found=binaryearch(arr,n,k);
	}

	if(found==-1)
	{
		cout<<"Not found"<<endl;
	}
	else
	{
		cout<<"found at index of:"<<found<<endl;
	}
	return 0;
}