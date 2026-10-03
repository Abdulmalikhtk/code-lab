/*
Queue will follow FIFO first in first out. 

Which element entered first it will remove first

We have 6 method:
Front,push,back,size,empty,pop
*/

// Online C++ compiler to run C++ program online
#include <iostream>
#include<queue>
using namespace std;
void displayqueue(queue<int> queue_values)
{
    cout<<"All queue elements:"<<endl;
    while(!queue_values.empty())
    {
        cout<<queue_values.front()<<endl;
        queue_values.pop();
    }
}
int main() {
    queue<int> queue_values;
    queue_values.push(10);
    queue_values.push(20);
    queue_values.push(5);
    queue_values.push(26);
    
    displayqueue(queue_values);
    
    cout<<"front element:"<<queue_values.front()<<endl;
    cout<<"back element:"<<queue_values.back()<<endl;
    cout<<"queue element size:"<<queue_values.size()<<endl;
    cout<<"After pop queue element size:"<<queue_values.size()<<endl;
    
    displayqueue(queue_values);
    
    queue_values.pop();
    queue_values.pop();
    queue_values.pop();
    
    cout<<"queue element size:"<<queue_values.size()<<endl;
    displayqueue(queue_values);

    return 0;
}
