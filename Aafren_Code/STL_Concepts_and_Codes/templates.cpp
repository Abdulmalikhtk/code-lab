/*

C++ template is a powerful tool for creating generic classes or functions. This allows us to write code that works for any data type without rewriting it for each type.
Key feature of templates :
	• Avoid code duplication by allowing one function or class to work with multiple data types, mainly allowing generic functions and classes.
	• Provide type safety, unlike using void* pointers or macros.
	• Can be specialized for specific data types when needed.
	• Form the basis of STL containers and algorithms like vector, map, and sort.
	
	
	Containers are boxes in which we store the data that requires processing 
The most common used containers are vector,list,map,set,stack,queue,etc;
Each contaioners provides different capabilities and benefits

To processing  we need algorithm sort searc group,find, compare,
we can able to write our own algorithm(function object)functors

To navigate we need iterators through the data


Containers are used to store data
Algorithm  are used to process the data
Iterators are used to navigate through the data
Functors are used to write our own custom algorithm
 

*/

// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

template <typename T>

class calculator
{
  public:
  T add(T a,T b)
  {
      return a+b;
  }
  T sub(T a,T b)
  {
      return a-b;
  }
  T mul(T a,T b)
  {
      return a*b;
  }
  T divi(T a,T b)
  {
      if(b==0)
      {
          cout<<"not divided by 0"<<endl;
          return 0;
      }
      return a/b;
  }
  T max(T a, T b)
  {
      return (a>b) ? a:b;
      
  }
};

int main() {
    calculator<int> intmycalculator;
    cout<<intmycalculator.add(2,3)<<endl;
    cout<<intmycalculator.sub(2,3)<<endl;
    cout<<intmycalculator.mul(2,3)<<endl;
    cout<<intmycalculator.divi(2,3)<<endl;
    cout<<intmycalculator.max(2,3)<<endl;
    
    
    calculator<float> floatmycalculator;
    cout<<floatmycalculator.add(2.2,3.3)<<endl;
    cout<<floatmycalculator.sub(2.2,3.3)<<endl;
    cout<<floatmycalculator.mul(2.2,3.3)<<endl;
    cout<<floatmycalculator.divi(2.2,3.3)<<endl;
    cout<<floatmycalculator.max(2.2,3.3)<<endl;
    
    calculator<string> stringmycalculator;
    cout<<stringmycalculator.add("Aafren","Fathima")<<endl;
    cout<<stringmycalculator.max("Aafren","Fathima")<<endl;
    
    calculator<char> charmycalculator;
    cout<<stringmycalculator.add("G","E")<<endl;
    cout<<stringmycalculator.max("g","e")<<endl;
    
    
    

    return 0;
}

