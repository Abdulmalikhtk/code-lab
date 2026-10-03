// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v={1,2,3,5,6,7,2,5};
    for(auto i=0;i<v.size();i++)
    {
        for(auto j=i+1;j<v.size();j++)
        {
            if(v[i]==v[j])
            {
                cout<<"dublicate found:"<<v[i]<<endl;
            }
        }
    }

    return 0;
}
