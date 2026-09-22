#include <iostream>
#include <string>
using namespace std;

unsigned int countSetBits(unsigned int n) {
    unsigned int count = 0;
    while (n > 0) {
        count += (n & 1); // Check the least significant bit
        n >>= 1;         // Right shift to check the next bit
    }
    return count;
}

int biwiseoperator(int n) {

    int m=n>>3;
    // std::cout<<m;
    return m;
}
int stringtoint(string str)
{
   int n=str.length();
   int result =0;
 for(int i=0;i<n;i++)
 {
     if(str[i]>='0' || str[i]>='9')
     {
         result=result*10+(str[i]-'0');
     }
 }
 return result;
}


int main() {
    int num = 64; // Example: 29 in binary is 11101
    std::cout << "Number of 1s in " << num << ": " << countSetBits(num) << std::endl;
    std::cout << "Number of 1s in " << num << ": " << biwiseoperator(num) << std::endl;
    string str="12345";
    std::cout << "Number of 1s in " << num << ": " << stringtoint(str) << std::endl;
    return 0;
}
