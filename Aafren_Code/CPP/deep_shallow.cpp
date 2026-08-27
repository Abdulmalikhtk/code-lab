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
      age=t.age;
      name=t.name;
  }
  Test(const Test& t)
  {
      age=t.age;
      name=new string(*(t.name));
  }
  void show()
  {
      cout<<"name:"<<*name<<" Age:"<<age<<endl;
  }
};
int main() {
    Test t1(27,"Charlie");
    t1.show();

    Test t2(30,"Daniel");
    t2.show();

    Test t3(t1);
    t3.show();
	t2.show();
    t1.show();

    Test t4(t2,true);

    t4.show();
    t2.show();

    *(t4.name)="bob";
    t4.show();
    t2.show();

    *(t3.name)="alice";
    t3.show();
    t1.show();


    cout<<"t1 and t2 are "<<(t1==t2? "equal":"Not equal")<<endl;
    return 0;
}
