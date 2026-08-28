// Online C++ compiler to run C++ program online
#include <iostream>
#include <thread>
#include<chrono>
#include<mutex>

using namespace std;
mutex mt;

void takeOrder(int id)
{
    lock_guard<mutex> test(mt);
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"Taking order for table number:"<<id<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"order taken for table number:"<<id<<endl;
}
void processOrder(int id)
{
    lock_guard<mutex> test(mt);
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"Processing order for table number:"<<id<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"Order Processed for table number:"<<id<<endl;
}
void servedOrder(int id)
{
    lock_guard<mutex> test(mt);
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"Serving order for table number:"<<id<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"Order served for table number:"<<id<<endl;
}


int main() {
    cout<<"Restaurent scenario based implementation"<<endl;
    int id=5;
    while(true)
    {
    // Inside main() while loop:
    thread t1(takeOrder, id);
    t1.join(); // Block main until t1 finishes taking the order

    thread t2(processOrder, id);
    t2.join(); // Block main until t2 finishes cooking the order

    thread t3(servedOrder, id);
    t3.join(); // Block main until t3 finishes serving the order
    id++;
    if(id==9)
    {
        break;
    }
    }


    return 0;
}

/*

Taking order for table number:5
order taken for table number:5
Processing order for table number:5
Order Processed for table number:5
Serving order for table number:5
Order served for table number:5
Taking order for table number:6
order taken for table number:6
Processing order for table number:6
Order Processed for table number:6
Serving order for table number:6
Order served for table number:6
Taking order for table number:7
order taken for table number:7
Processing order for table number:7
Order Processed for table number:7
Serving order for table number:7
Order served for table number:7
Taking order for table number:8
order taken for table number:8
Processing order for table number:8
Order Processed for table number:8
Serving order for table number:8
Order served for table number:8

*/
