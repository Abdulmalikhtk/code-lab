// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Rectangle
{
  public:
  int l;
  int b;
  Rectangle(int length,int breadth)
  {
      cout<<"Constructor called"<<endl;
      l=length;
      b=breadth;

  }
  ~Rectangle()
  {
      cout<<"Destructor called"<<endl;
  }
  void area()
    {
        cout<<"area of rectangle:"<<l*b<<endl;
    }
};
int main() {

    unique_ptr<Rectangle> test=make_unique<Rectangle>(10,9);
    {
        test->area();
    }
    {
    unique_ptr<Rectangle> test1=make_unique<Rectangle>(10,2);
    // test1=move(test);
    test1->area();
    }
    test->area();

    cout<<"---------------------------------------------------------"<<endl;
    shared_ptr<Rectangle> s_test=make_shared<Rectangle>(10,9);
    {
        s_test->area();
    }
    {
    shared_ptr<Rectangle> s_test1=make_shared<Rectangle>(10,2);
    // s_test1=s_test;
    s_test1->area();
    }
    s_test->area();

    cout<<"---------------------------------------------------------"<<endl;
    shared_ptr<Rectangle> s_test1=make_shared<Rectangle>(10,9);
    weak_ptr<Rectangle> w_test;
     w_test=s_test1;

    return 0;
}
