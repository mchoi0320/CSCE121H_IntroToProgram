#include <iostream>
#include <iomanip>
//#include <cassert>
#include "person.hpp"
#include "container.hpp"
#include "building.hpp"
using namespace std;

Person::Person(int i, int t, int s, int d)
{
    id = i;
    start = t;
    src = s;
    dest = d;
    embarkTime = -1;
    arriveTime = -1;
}
/*
bool operator==(const Person& p)
{
    return (id == p.id);
}

bool operator<(const Person& p)
{
    return (start < p.start);
}
*/
bool operator==(const Person& p1, const Person& p2)
{
    return (p1.id == p2.id);
}

bool operator<(const Person& p1, const Person& p2)
{
    return (p1.start < p2.start);
}

void Person::setEmbarkTime(int x)
{
    embarkTime = x;
}

void Person::setArriveTime(int x)
{
    arriveTime = x;
}

Dir Person::dir()
{
    //assert(src != dest);
    //if (dest < src) return DOWN;
    //else return UP;
    return (dest < src) ? DOWN : UP;
}

void Person::print()
{
    cout << "PERSON ID "; cout << setw(2) << id << ' ';
    cout << "src "; cout << setw(1) << src << ' ';
    cout << "dest "; cout << setw(1) << dest << ' ';
    cout << "start "; cout << setw(2) << start << ' ';
    cout << "embarked "; cout << setw(2) << embarkTime << ' ';
    cout << "arrived "; cout << setw(2) << arriveTime << ' ';
    
    if (arriveTime != -1) {
        int travelTime = arriveTime - start;
        cout << "traveltime "; cout << setw(2) << travelTime; }
    cout << endl;
}
