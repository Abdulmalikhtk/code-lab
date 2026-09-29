#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

mutex mt;

void takeOrder(int id)
{
	lock_guard<mutex> lock(mt);
	cout<<"Taking order for table number:"<<id<<endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout<<"Order taken for table number:"<<id<<endl;
	this_thread::sleep_for(chrono::seconds(1));
}

void processOrder(int id)
{
	lock_guard<mutex> lock(mt);
	cout<<"Processing order for table number:"<<id<<endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout<<"Order processed for table number:"<<id<<endl;
	this_thread::sleep_for(chrono::seconds(1));
}

void serveOrder(int id)
{
	lock_guard<mutex> lock(mt);
	cout<<"Serving order for table number:"<<id<<endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout<<"Order served for table number:"<<id<<endl;
	this_thread::sleep_for(chrono::seconds(1));
}

int main()
{
	int id=5;
	thread t1(takeOrder,id);
	thread t2(processOrder,id);
	thread t3(serveOrder,id);

	t1.join();
	t2.join();
	t3.join();


	return 0;
}