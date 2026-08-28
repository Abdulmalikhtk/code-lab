#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

mutex mt;
condition_variable cv;
queue<int> buffer;
bool done = false;
const unsigned MAX_BUFF_SIZE = 5;

void producer()
{
    int value = 0;
    while(value < 10)
    {
        {
            // Lock is strictly isolated inside this scoped block
            unique_lock<mutex> lock(mt);
            cv.wait(lock, []{ return buffer.size() < MAX_BUFF_SIZE; });

            cout << "Produced Value: " << value << endl;
            buffer.push(value);
            value++;
        } // Lock safely and automatically destroys/unlocks here

        cv.notify_all();
        this_thread::sleep_for(chrono::seconds(1)); // Sleeping safely OUTSIDE the lock
    }

    {
        unique_lock<mutex> lock(mt);
        done = true;
    }
    cv.notify_all();
}

void consumer()
{
    while(true)
    {
        int value = -1;
        bool should_exit = false;

        {
            unique_lock<mutex> lock(mt);
            cv.wait(lock, []{ return !buffer.empty() || done; });

            if (buffer.empty() && done)
            {
                should_exit = true;
            }
            else if (!buffer.empty())
            {
                value = buffer.front();
                buffer.pop();
            }
        } // Lock safely and automatically destroys/unlocks here

        cv.notify_all();

        if (should_exit) {
            break; // Breaking here is perfectly safe because the lock is already released!
        }

        if (value != -1) {
            cout << "Consumed Value: " << value << endl;
            this_thread::sleep_for(chrono::seconds(1)); // Processing work happens OUTSIDE the lock
        }
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}


/*
Produced Value: 0
Consumed Value: 0
Produced Value: 1
Consumed Value: 1
Produced Value: 2
Consumed Value: 2
Produced Value: 3
Consumed Value: 3
Produced Value: 4
Consumed Value: 4
Produced Value: 5
Consumed Value: 5
Produced Value: 6
Consumed Value: 6
Produced Value: 7
Consumed Value: 7
Produced Value: 8
Consumed Value: 8
Produced Value: 9
Consumed Value: 9

*/
