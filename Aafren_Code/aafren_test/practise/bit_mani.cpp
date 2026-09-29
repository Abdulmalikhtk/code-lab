#include <iostream>
using namespace std;

int bitreverse(int n)
{
	int res=0;
	for(int i=0;i<4;i++)
	{
		res<<=1;
		res|=(n&1);
		n=n>>1;
	}
	return res;

}
void reverseWord(string &str,int start, int end)
{
	while(start<end)
	{
		char temp=str[start];
		str[start]=str[end];
		str[end]=temp;
		start++;
		end--;
	}
}
string reverseEachword(string str)
{
	int start=0;
	for(int i=0;i<=str.length();i++)
	{
		if(str[i]==' '||str[i]=='\0')
		{
			reverseWord(str,start,i-1);
			start=i+1;
		}
	}
	return str;
}
void anotherreverseWord(char *str,int start, int end)
{
	while(start<end)
	{
		char temp=str[start];
		str[start]=str[end];
		str[end]=temp;
		start++;
		end--;
	}
}
char* anotherreverseEachword(char *str)
{
	int start=0;
	int i=0;
	while(str[i]!='\0')
	{
		if(str[i]==' ')
		{
			anotherreverseWord(str,start,i-1);
			start=i+1;
		}
		i++;
	}
	anotherreverseWord(str,start,i-1);

	return str;
}
void findLSBpoition(int value)
{
	unsigned int lsb=value&1;
	cout<<"LSB value is :"<<lsb<<endl;

}
void findMSBpoition(int value)
{
	unsigned int msb=(value>>31)&1;
	cout<<"MSB value is :"<<msb<<endl;
}
void swapNumbersWithoutTemp()
{
	int a=10,b=28;
	cout<<"A value:"<<a<<endl;
	cout<<"B value:"<<b<<endl;

	a=a+b;
	b=a-b;
	a=a-b;

	cout<<"A value:"<<a<<endl;
	cout<<"B value:"<<b<<endl;
}
int main()
{

	int n=13;
	cout<<"Actual value:"<<n<<endl;
	int result=bitreverse(n);
	cout<<"reversed value:"<<result<<endl;
	int value=12637;
	findLSBpoition(value);
	findMSBpoition(value);

	string str="Hi i am aafren";
	string result1=reverseEachword(str);
	cout<<"Reversed each word in sentence result:"<<result1<<endl;

	char str1[]="Hi i am Deepak";
	char *result2=anotherreverseEachword(str1); // this is most optimized code
	cout<<"Reversed each word in sentence result:"<<result2<<endl;

	swapNumbersWithoutTemp();


	return 0;
}