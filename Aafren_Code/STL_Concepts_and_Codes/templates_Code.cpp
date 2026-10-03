// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

template <typename T>
class calculator
{
  public:
  T a;
  T b;
  calculator(T a1,T b1)
  {
      a=a1;
      b=b1;
  }
  T add()
  {
      return a+b;
  }
  T sub()
  {
      return a-b;
  }
  T mul()
  {
      return a*b;
  }
  T divi()
  {
      if(b==0)
      {
          cout<<"not divided by 0"<<endl;
          return 0;
      }
      return a/b;
  }
  T max()
  {
      return (a>b) ? a:b;
      
  }
};

int main() {
    calculator<int> intmycalculator(2,3);
    cout<<intmycalculator.add()<<endl;
    cout<<intmycalculator.sub()<<endl;
    cout<<intmycalculator.mul()<<endl;
    cout<<intmycalculator.divi()<<endl;
    cout<<intmycalculator.max()<<endl;
    
    
    calculator<float> floatmycalculator(2.2,3.3);
    cout<<floatmycalculator.add()<<endl;
    cout<<floatmycalculator.sub()<<endl;
    cout<<floatmycalculator.mul()<<endl;
    cout<<floatmycalculator.divi()<<endl;
    cout<<floatmycalculator.max()<<endl;
    
    calculator<string> stringmycalculator("Aafren","Fathima");
    cout<<stringmycalculator.add()<<endl;
    cout<<stringmycalculator.max()<<endl;
    
    calculator<char> charmycalculator('g','e');
    cout<<charmycalculator.add()<<endl;
    cout<<charmycalculator.max()<<endl;
    
    
    

    return 0;
}
