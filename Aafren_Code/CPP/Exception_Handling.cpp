// Online C++ compiler to run C++ program online
#include <iostream>
using std::cout,std::endl;

class DivisibleByZeroException
{
  public:
  void showMessage()
  {
      cout<<"divide by zero"<<endl;
  }
};
double division(double a,double b)
{
    if(b==0)
        throw DivisibleByZeroException();
    return a/b;
}
int main() {
    double a=5;
    
    double b=0;
    try
    {
    double result=division(a,b);
    }
    catch(DivisibleByZeroException e)
    {
        e.showMessage();
    }
    catch(int e)
    {
        cout<<"catched value from try block "<<e<<endl;
    }
    catch(...)
    {
        cout<<"default catch block to catch all the types"<<endl;
    }

    return 0;
}
