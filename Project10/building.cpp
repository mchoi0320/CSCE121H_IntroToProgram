#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "person.hpp"
#include "container.hpp"
#include "building.hpp"
using namespace std;

void Building::AddPerson(Person p)
{
    // add person to list of people
    persons.push_back(p);
}

void Building::RemovePerson(Person p)
{
    // remove person from list of people
    for (int i=0; i<persons.size(); i++) {
        if (persons[i] == p) {
            persons.erase(persons.begin()+i); } }
}

void Building::readin_traffic(char* fname)
{
    ifstream file; file.open(fname);

    // check that command-line arguments match file contents
    string firstLine; getline(file, firstLine);
    istringstream ss(firstLine);
    vector<int> tempVec; string tempStr; 
    int i=1;
    while (ss >> tempStr) {
        if (i%2 == 0) {
            //tempVec.push_back(stoi(tempStr));
            tempVec.push_back(atoi(tempStr.c_str())); }
        i++; }
    assert(nfloors == tempVec[0] && ITERS == tempVec[1]);

    // read in traffic file & store data for all persons
    string line, val;
    while (getline(file, line)) {
        istringstream ss(line);
        vector<int> temp;
        int i=0;
        while (ss >> val) {
            if (i%2 == 0 && i != 0) {
                //temp.push_back(stoi(val));
                temp.push_back(atoi(val.c_str())); }
            i++; }
        Person tempObj(temp[0], temp[1], temp[2], temp[3]);
        AddPerson(tempObj); }

    file.close();
}

Building::Building(int numiters, int numfloors, int numcars, char* fname)
{
    ITERS = numiters;
    nfloors = numfloors;
    ncars = numcars;
    readin_traffic(fname);

    for (int i=0; i<nfloors; i++) {
        Floor tempObj(i);
        floors.push_back(tempObj); }

    for (int i=0; i<ncars; i++) {
        Car tempObj(i, nfloors);
        cars.push_back(tempObj); }
}

void Building::NewArrivals(int iter)
{
    // check for newly arrived person (start time = iter)
    vector<Person>::iterator i = persons.begin();
    while (i != persons.end()) {
    //for (vector<Person>::iterator i=persons.begin(); i!=persons.end(); i++) {     // using a for loop would work if no one was being removed
        if ((*i).start == iter) {
            // move person to their source floor
            floors[(*i).src].AddPerson(*i);
            cout << "> New PERSON " << (*i).id << " arriving on Floor " << (*i).src << ", destination: Floor " << (*i).dest << endl;
            
            // press UP/DOWN button
            if ((*i).dest > (*i).src) floors[(*i).src].PressUp();
            else floors[(*i).src].PressDown();
            /*switch((*i).dir) {
                case UP:
                    floors[(*i).src].PressUp;
                case DOWN:
                    floors[(*i).src].PressDown; }*/

            RemovePerson(*i); }
        else i++; } // increment only when no one was removed
}

void Building::summary()
{
    cout << "\n------------------------------SUMMARY------------------------------" << endl;
    
    cout << "WAITING:\n";
    int k=0;
    for (int i=0; i<floors.size(); i++) {
        if (floors[i].persons.size() > 0) {
            k++;
            sort(floors[i].persons.begin(), floors[i].persons.end());
            for (int j=0; j<floors[i].persons.size(); j++) {
                cout << "On Floor " << i << ": ";
                floors[i].persons[j].print(); } } }
    if (k == 0) cout << "NONE\n";

    cout << "\nTRAVELLING:\n";
    k=0;
    for (int i=0; i<cars.size(); i++) {
        if (cars[i].persons.size() > 0) {
            k++;
            sort(cars[i].persons.begin(), cars[i].persons.end());
            for (int j=0; j<cars[i].persons.size(); j++) {
                cout << "In CAR" << i << ": ";
                cars[i].persons[j].print(); } } }
    if (k == 0) cout << "NONE\n";

    cout << "\nARRIVED:\n";
    sort(persons.begin(), persons.end());
    for (int i=0; i<persons.size(); i++) {
        persons[i].print(); }

    cout << endl;
}

void Building::run()
{
    for (int iter=0; iter<ITERS; iter++) {
        cout << endl << "-------" << endl << "Time " << iter << endl << "-------" << endl;
        
        // check for Persons whose start time is now, move to source floor
        NewArrivals(iter);

        // print out contents of floors and cars
        for (int i=0; i<nfloors; i++) { 
            int f = (nfloors - 1) - i;
            cout << "FLOOR " << f << ", ";
            floors[f].printContents(); 
        
            for (int j=0; j<ncars; j++) {
                if (cars[j].floor == f) {
                    cout << "   CAR" << j;
                    cars[j].printSymbolic(); } }
            cout << endl; }

        for (int i=0; i<ncars; i++) {
            cout << "CAR " << i << ", ";
            cars[i].printContents(); }

        // update cars...
        for (int i=0; i<ncars; i++) {
            cars[i].update(floors, iter, persons); } }
    cout << endl;
}
