// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

void strcopy(char source[],char destination[])
{
    int i=0;
    while(source[i]!='\0')
    {
        destination[i]=source[i];
        // source++;
        // destination++;
        i++;
    }
}
void stringcopy(char* source,char* destination)
{
    while(*source!='\0')
    {
        *destination=*source;
        source++;
        destination++;
    }
}
int main() {
    char source[20]="Aafren Fathima";
    char destination[20]="";

    cout<<"source string:"<<source<<endl;
    cout<<"destination string:"<<destination<<endl;

    strcopy(source,destination);
    cout<<"source string:"<<source<<endl;
    cout<<"destination string:"<<destination<<endl;

    stringcopy(source,destination);
    cout<<"source string:"<<source<<endl;
    cout<<"destination string:"<<destination<<endl;


    return 0;
}
