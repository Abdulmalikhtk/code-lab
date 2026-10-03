/*
vector:
Vector  have any size. We need specify any size.
Inserting and deleteing will be difficult. Time also more

Searching will be easy and more efficient

*/

// Online C++ compiler to run C++ program online
#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;



int main() {
    vector<int> v={1,2,4,5,6,7,7,8,8,4};
    
    sort(v.begin(),v.end());
    
    for(auto x:v)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    
    vector<int> v1;
    
    if(v1.empty())
    {
        cout<<"empty vector"<<endl;
    }
    else
    {
        cout<<"Not empty vector"<<endl;
    }
    
    for(int i=0;i<10;i++)
    {
        v1.push_back(i);
    }
    
    for(auto x:v1)
    {
        cout<<x<<" ";
    }
    
    cout<<endl;
    
    cout<<"size:"<<v1.size()<<endl;
    cout<<"capacity:"<<v1.capacity()<<endl;
    cout<<"max size:"<<v1.max_size()<<endl;
    
    if(v1.empty())
    {
        cout<<"empty vector"<<endl;
    }
    else
    {
        cout<<"Not empty vector"<<endl;
    }
    cout<<"front:"<<v1.front()<<endl;
    cout<<"back:"<<v1.back()<<endl;
    v1.insert(v1.begin()+5,99);
    for(auto x:v1)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    v1.erase(v1.begin()+5);
    for(auto x:v1)
    {
        cout<<x<<" ";
    }
    v1.clear();
    if(v1.empty())
    {
        cout<<"empty vector"<<endl;
    }
    else
    {
        cout<<"Not empty vector"<<endl;
    }
    
    
    return 0;
}
