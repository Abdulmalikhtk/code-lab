#include <iostream>

using std::cout,std::endl;


void reverse_number(int number)
{
	int actual_number=number;
	cout<<"Actual value:"<<actual_number<<endl;
	int result=0;
	while(number>0)
	{
		int remainder=number%10;
		result=remainder+10*result;
		number=number/10;
	}
	cout<<"Reversed Number:"<<result<<endl;

}
int main()
{
	int number=12345;
	reverse_number(number);


	return 0;

}

	