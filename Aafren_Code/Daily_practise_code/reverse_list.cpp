// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

int main() {
    int n=12345;
    int rev=0;

    while(n>0)
    {
        int remainder=n%10;
        rev=rev*10+remainder;
        n=n/10;
    }
    cout<<"result:"<<rev;
    return 0;
}
