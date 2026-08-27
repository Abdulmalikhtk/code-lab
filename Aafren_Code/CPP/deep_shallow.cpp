// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
class Test
{
  public:
  string* name;
  int age;

  Test(int a,string n)
  {
      age=a;
      name=new string(n);
  }

  bool operator==(const Test& t)
  {
      return age==t.age;
  }

  Test(const Test& t,bool shallow)
  {
    cout<<"Shallow copy------------"<<endl;
      age=t.age;
      name=t.name;
  }
  Test(const Test& t)
  {
    cout<<"Deep copy-------------"<<endl;
      age=t.age;
      name=new string(*(t.name));
  }
  void show()
  {
      cout<<"name:"<<*name<<" Age:"<<age<<endl;
  }
};
int main() {
    cout<<"t1 object----------"<<endl;
    Test t1(27,"Charlie");
    t1.show();
    cout<<"----------------------------------------"<<endl;

    cout<<"t2 object----------------"<<endl;
    Test t2(30,"Daniel");
    t2.show();
    cout<<"----------------------------------------"<<endl;

    cout<<"t3 object deep copy-----------"<<endl;
    Test t3(t1);
    t3.show();
    t1.show();
    cout<<"----------------------------------------"<<endl;

    cout<<"t4 object shallow copy------"<<endl;
    Test t4(t2,true);

    t4.show();
    t2.show();
    cout<<"----------------------------------------"<<endl;

    cout<<"t4 object name change shallow copy------"<<endl;
    *(t4.name)="bob";
    t4.show();
    t2.show();
    cout<<"----------------------------------------"<<endl;

    cout<<"t2 object name change deep copy------"<<endl;
    *(t3.name)="alice";
    t3.show();
    t1.show();
    cout<<"----------------------------------------"<<endl;


    cout<<"t1 and t2 are "<<(t1==t2? "equal":"Not equal")<<endl;
    return 0;
}
