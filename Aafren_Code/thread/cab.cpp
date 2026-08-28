/*

What is a Process?
A process is an independent program in execution. It has its own memory space, resources, and system state. Think of it like a separate application running on your computer.
	• Each process is isolated from others.
	• It has its own address space (memory).
	• Communication between processes is harder (requires IPC – Inter-Process Communication).

What is a Thread?
A thread is a smaller unit of a process. Multiple threads can run within a single process and share the same memory.
	• Threads are lightweight.
	• They share memory and resources of the parent process.
	• Communication between threads is easier.


Imagine a process is like a house, and threads are the people living inside.
	• Each house (process) has its own rooms (memory).
	• People (threads) inside the same house can easily talk and share things.
	• People in different houses need phones or letters to communicate (IPC).


Thread Life Cycle: A thread is born (Created), moves to ready/running (Executable), pauses via locks/sleeps (Blocked), and ends permanently once its function returns (Terminated)..
join(): This function stops the main program thread from moving forward until the target background thread finishes running completely.
*/

#include <iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

mutex mt;
void drivingCar(string drivername)
{
    lock_guard<mutex> test(mt);
    this_thread::sleep_for(chrono::seconds(2));
    cout<<drivername<<" is driving the car"<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout<<drivername<<" is stopped the car"<<endl;
}
int main()
{
    thread owner1(drivingCar,"Alice");
    thread owner2(drivingCar,"Bob");

    owner1.join();
    owner2.join();

    return 0;

}



/*
output

Alice is driving the car
Alice is stopped the car
Bob is driving the car
Bob is stopped the car

*/
