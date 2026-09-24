#include <iostream>

using namespace std;

int main()
{
    int arr[]={3,0,1,5,2,6,4};
    int n=sizeof(arr)/sizeof(arr[0]);   // one number missing from range 0..n

    // ---- Method 1: sum formula ----
    long long expectedSum = (long long)n * (n+1) / 2;
    long long actualSum = 0;

    for(int num : arr)
    {
        actualSum += num;
    }

    cout << "Missing Number (sum method): " << expectedSum - actualSum << endl;

    // ---- Method 2: XOR ----
    int missing = n;                    // start with the top of the range

    for(int i = 0; i < n; i++)
    {
        missing ^= i ^ arr[i];
    }

    cout << "Missing Number (XOR method): " << missing << endl;

    return 0;
}
