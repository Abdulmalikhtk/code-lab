/*
List:
List don't have any size. We don’t need specify any size dynamically it will
Grow. Inserting and deleteing will be easy. Time also reduce

Searching will take lot of time not efficient


List<int> myList;

myList.push_back(10);
myList.push_back(20);
myList.push_front(30);

myList.erase(myList.begin());

For(list<int>::iterator it=myList.begin();it!=myList.end();it++)
{
Cout<<*it<<endl;
}
*/


Relatime project:

#include <iostream>
#include <list>

using namespace std;

void displayRating(const list<int>& players)
{
    for(list<int>::const_iterator it=players.begin();it!=players.end();it++)
    {
        cout<<"Player Rating:"<<*it<<endl;
    }
}

void sortPlayerList(int rating,list<int>& players)
{
    for(list<int>::iterator it=players.begin();it!=players.end();it++)
    {
        if(*it>rating)
        {
            players.insert(it,rating);
            return;
        }
    }
    players.push_back(rating);
}

int main() {
    list<int> palyersRating={1,3,3,5,6,8,8,6,4,2,7,9};
    list<int> beginners;
    list<int> pros;
    
    for(list<int>::iterator it=palyersRating.begin();it!=palyersRating.end();it++)
    {
        int rating=*it;
        if(rating>=1&& rating<=5)
        {
            // beginners.push_back(*it);
            sortPlayerList(rating,beginners);
        }
        else if(rating>=6&& rating<=9)
        {
            sortPlayerList(rating,pros);
            // pros.push_back(*it);
        }
    }
    
    cout<<"beginers:"<<endl;
    displayRating(beginners);
    cout<<"Pros:"<<endl;
    displayRating(pros);

    return 0;
}

