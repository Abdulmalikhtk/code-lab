// Online C++ compiler to run C++ program online
#include <iostream>
#include <mutex>
#include <condition_variable>
#include<thread>
using namespace std;

mutex mt;
condition_variable cv;
bool oddturn=true;

void printOddNumber(int limit)
{
    for(int i=1;i<limit;i+=2){

    unique_lock<mutex> lock(mt);
    cv.wait(lock,[] {return oddturn;});
    cout<<i<<" ";
    oddturn=false;
    lock.unlock();
    cv.notify_all();
    }
}
void printEvenNumber(int limit)
{
     for(int i=2;i<=limit;i+=2){

    unique_lock<mutex> lock(mt);
    cv.wait(lock,[] {return !oddturn;});
    cout<<i<<" ";
    oddturn=true;
    lock.unlock();
    cv.notify_all();
     }
}
int main() {
    int limit=10;
    thread t1(printOddNumber,limit);
    thread t2(printEvenNumber,limit);

    t1.join();
    t2.join();
    return 0;
}
/*
1 2 3 4 5 6 7 8 9 10
*/



/*
When to Use What?
Situation
Use
Single variable (int, bool, pointer) counter/flag std::atomic
Multiple variables that must stay consistent together std::mutex
Complex critical section (multiple statements) std::mutex
Simple flag / counter / stop signal std::atomic


*/
