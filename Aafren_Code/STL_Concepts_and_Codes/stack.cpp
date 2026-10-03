/*Stack will follow LIFO last in first out. 

Which element entered last it will pop out first

We have 5 method:
Push,pop,top,size,empty
*/


// Online C++ compiler to run C++ program online
#include <iostream>
#include <stack>
using namespace std;

void dispalystack(stack<int> stack_values)
{
    cout<<"All stack elements:"<<endl;
    while(!stack_values.empty())
    {
        cout<<stack_values.top()<<endl;
        stack_values.pop();
    }
}

int main() {
    stack<int> stack_values;
    stack_values.push(10);
    stack_values.push(20);
    stack_values.push(5);
    stack_values.push(26);
    
     dispalystack(stack_values);
    
    cout<<"top element:"<<stack_values.top()<<endl;
    cout<<"Stack element size:"<<stack_values.size()<<endl;
    stack_values.pop();
    cout<<"After pop stack element size:"<<stack_values.size()<<endl;
    
    dispalystack(stack_values);
    
    stack_values.pop();
    stack_values.pop();
    stack_values.pop();
    
    cout<<"Stack element size:"<<stack_values.size()<<endl;
    dispalystack(stack_values);
    
    

    return 0;
}
