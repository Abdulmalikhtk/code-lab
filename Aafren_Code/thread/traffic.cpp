#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

std::mutex mtx;

void delayedresponse()
{
    for(int i=0;i<10;i++)
    {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    {
    std::lock_guard<std::mutex> lock(mtx);
    cout<<"Green Ligt ON"<<endl;
    }
     std::this_thread::sleep_for(std::chrono::seconds(2));
    {
    std::lock_guard<std::mutex> lock(mtx);
    cout<<"Red Light ON"<<endl;
    }

}
}
int main(){
cout<<"Traffic signal simulation"<<endl;
std::thread t(delayedresponse);
t.join();
return 0;
}


/*

Traffic signal simulation
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON
Green Ligt ON
Red Light ON

*/
