/*

Map is key value pairs like dictionary

map will print everthing in alhabetical order
Unordered map will show in the normal insertion order


*/

// Online C++ compiler to run C++ program online
#include <iostream>
#include <map>
#include<list>
#include<unordered_map>

using namespace std;


int main() {
    
    map<string,string> mymap;
    // mymap.insert({{"FName","Aafren"},{"LName","Fathima"},{"Age","27"}});
    
    mymap.insert(pair<string,string>("FName","Aafren"));
    mymap.insert(pair<string,string>("LName","Fathima"));
    mymap.insert(pair<string,string>("Age","27"));
    
    mymap["LName"]="Deepak";
    for(auto s:mymap)
    {
        cout<<s.first<<":"<<s.second<<endl;
    }
    
    cout<<"unordered map::::::::::::::::"<<endl;
    
    unordered_map<string,string> mymap1;
    // mymap.insert({{"FName","Aafren"},{"LName","Fathima"},{"Age","27"}});
    
    mymap1.insert(pair<string,string>("FName","Aafren"));
    mymap1.insert(pair<string,string>("LName","Fathima"));
    mymap1.insert(pair<string,string>("Age","27"));
    
    
    for(auto s:mymap1)
    {
        cout<<s.first<<":"<<s.second<<endl;
    }
    
    
    map<string,list<string>> mymap3;
    
    list<string> ls1={"Aafren","Fathima","M"};
    list<string> ls2={"Aafren","Fathima","Mohamed","Kasim","Chagle"};
    list<string> ls3={"Aafren","Fathima","Zakira","Begum"};
    
    mymap3.insert(pair<string,list<string>>("option1",ls1));
    mymap3.insert(pair<string,list<string>>("option2",ls2));
    mymap3.insert(pair<string,list<string>>("option3",ls3));
    
    for(auto s:mymap3)
    {
        cout<<s.first<<":";
        for(auto l:s.second)
        {
            cout<<l;
        }
        cout<<endl;
    }

    return 0;
}
