/*
std::atomic is not really a "lock" — it's a way to make individual variable operations indivisible (uninterruptible) without using a mutex. Threads never block; the CPU guarantees the operation completes as one unit.
Analogy:
Mutex = a room with a door. Only one person inside at a time. Others wait outside.
Atomic = a vending machine transaction. The whole "insert coin → get item" happens in one uninterruptible step. No door, no waiting.

mutex Works, but slow — every increment locks/unlocks a mutex (kernel-level cost).
atomic Much faster — uses special CPU instructions (LOCK XADD on x86). No blocking, no waiting.
*/


#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> counter{0};  // atomic — thread-safe by design

void increment() {
    for (int i = 0; i < 100000; i++)
        counter++;   // now indivisible at CPU level
}

int main() {
    thread t1(increment), t2(increment);
    t1.join(); t2.join();
    cout << "Counter = " << counter << endl;  // Always 200000
}

/*
Counter = 200000
*/


/*
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> ticketNumber{0};

void customer(string name) {
    int myTicket = ++ticketNumber;   // atomic increment + read
    cout << name << " got ticket #" << myTicket << endl;
}

int main() {
    thread t1(customer, "Malik");
    thread t2(customer, "Aafren");
    thread t3(customer, "Ravi");
    t1.join(); t2.join(); t3.join();
}



Key Atomic Operations
atomic<int> x{0};

x.store(10);            // write
int v = x.load();       // read
x++;                    // atomic increment
x--;                    // atomic decrement
x.fetch_add(5);         // add 5, return old value
x.exchange(20);         // set to 20, return old value

*/
