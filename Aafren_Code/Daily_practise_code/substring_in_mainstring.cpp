// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
using namespace std;



int main() {
    string mainstring="Hi this is aafren";
    string substring="this";

    int found=mainstring.find(substring);

    if(found!=string::npos)
    {
        cout<<"substring "<<substring<<" is found in mainstring "<<mainstring<<" at the position of: "<<found<<endl;
    }
    else
    {
        cout<<"substring "<<substring<<" is not found in mainstring "<<mainstring<<endl;
    }


    return 0;
}
