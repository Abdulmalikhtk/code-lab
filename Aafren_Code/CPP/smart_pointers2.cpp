// Online C++ compiler to run C++ program online
#include <iostream>
#include <memory>

using namespace std;
class Test
{
    int a;
    int b;
  public:
  Test(int one,int two)
  {
      cout<<"contructor called"<<endl;
      a=one;
      b=two;
  }
   ~Test()
  {
      cout<<"Destructor called"<<endl;
  }
  int add()
  {
      return a+b;
  }

};
int main() {
    // unique pointer
    {
    std::unique_ptr<Test> test1=std::make_unique<Test>(6,9);
{
    std::unique_ptr<Test> test2=std::make_unique<Test>(10,9);
    {
    std::unique_ptr<Test> test3=std::make_unique<Test>(12,9);
    cout<<"3Addition of two numbers:"<<test3->add()<<endl;
    }
    cout<<"2Addition of two numbers:"<<test2->add()<<endl;
    test1=move(test2);
    // cout<<"2Addition of two numbers:"<<test2->add()<<endl;
    }
    cout<<"1Addition of two numbers:"<<test1->add()<<endl;
    }
    //unique end
    cout<<"--------------------------------------------"<<endl;

    //shared pointer
    {
    std::shared_ptr<Test> test2=std::make_shared<Test>(4,9);
    cout<<"5Addition of two numbers:"<<test2->add()<<endl;
    {
    std::shared_ptr<Test> test1=std::make_shared<Test>(3,9);
    cout<<"4Addition of two numbers:"<<test1->add()<<endl;
    test2=test1;
    cout<<"4Addition of two numbers:"<<test1->add()<<endl;
    }
    cout<<"5Addition of two numbers:"<<test2->add()<<endl;
    }
    //shares pointer end
    cout<<"--------------------------------------------"<<endl;

    //weak pointer
     {
    std::shared_ptr<Test> test2=std::make_shared<Test>(5,9);
    {
    cout<<"5Addition of two numbers:"<<test2->add()<<endl;
    std::weak_ptr<Test> weak;
    weak=test2;
    }
     }
     // weak pointer end
    return 0;

}
