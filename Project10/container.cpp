#include <iostream>
#include <cstdlib>
#include "person.hpp"
#include "container.hpp"
#include "building.hpp"
using namespace std;

//-------Base Class Container-------
void Container::Press(int f)
{
    // press button for floor f
    buttons[f] = true;
}
  
bool Container::Pressed(int f)
{
    // status of button for floor f (pressed/not pressed)
    return buttons[f];
}

void Container::Reset(int f)
{
    // resets button status for floor f (pressed -> not pressed)
    buttons[f] = false;
}
  
void Container::AddPerson(Person p)
{
    // adds person to a floor/car
    persons.push_back(p);
}
  
void Container::RemovePerson(Person p)
{
    // removes person from a floor/car
    for (int i=0; i<persons.size(); i++) {
        if (persons[i] == p) {
            persons.erase(persons.begin()+i); } }
}


//-------Derived Class Floor-------
Floor::Floor(int i)
{
    // initialize ID
    id = i;
    
    // initialize two buttons (UP/DOWN) to false (not pressed)
    buttons.push_back(false);
    buttons.push_back(false);
}

bool Floor::UpPressed()
{
    // status of UP button (pressed/not pressed)
    return buttons[UP];
}
  
bool Floor::DownPressed()
{
    // status of DOWN button (pressed/not pressed)
    return buttons[DOWN];
}

void Floor::PressUp()
{
    // press UP button
    buttons[UP] = true;
}

void Floor::PressDown()
{
    // press DOWN button
    buttons[DOWN] = true;
}
  
void Floor::ClearUp()
{
    // reset UP button (pressed -> not pressed)
    buttons[UP] = false;
}

void Floor::ClearDown()
{
    // reset DOWN button (pressed -> not pressed)
    buttons[DOWN] = false;
}

void Floor::printContents()
{
    // print contents of floor in the following format:
    // FLOOR 4, persons 0, up 0, down 0
    cout << "persons " << persons.size() << ", up " << UpPressed() << ", down " << DownPressed();
}


//-------Derived Class Car-------
Car::Car(int i, int f)
{
    // initialize ID, number of floors in building, and state, starting floor, capacity, and direction of the elevator
    id = i;
    nfloors = f;
    state = IDLE;
    floor = rand()%nfloors;
    //floor = 0;
    capacity = 10;
    //dir = UP;
    if (floor == 0) dir = UP;
    else if (floor == nfloors - 1) dir = DOWN;
    else {
        int random = rand()%2;
        (random == 0) ? dir = DOWN : dir = UP; }
    
    // initialize buttons for floors to false (not pressed)
    for (int i=0; i<nfloors; i++) {
        buttons.push_back(false); }
}

void Car::printContents()
{
    // print contents of elevator in the following format:
    // CAR 0, floor 0, load 0, state 0, dir 1, buttonsPressed:
    cout << "floor " << floor << ", load " << persons.size() << ", state " << state << ", dir " << dir << ", buttonsPressed: ";
    for (int i=0; i<nfloors; i++) {
        if (Pressed(i)) cout << i << ' '; }
    cout << endl;
}

void Car::printSymbolic()
{
    // number of people in the elevator
    cout << '[' << persons.size() << ']';

    // state of the elevator (IDLE, MOVING UP/DOWN, or PROCESSING)
    if (state == IDLE) cout << '*';
    if (state == MOVING) {
        if (dir == UP) cout << '^';
        else cout << 'v'; }
    if (state == PROCESSING || state == CLOSED) cout << '~';
}

void Car::update(vector<Floor>& floors, int iter, vector<Person>& allpersons)   // take in vector<Floor> and vector<Person> from building
{
    // the elevator is IDLE when there are no buttons pressed or there are no people in the car and floors
    if (state == IDLE) {
        // check for buttons that have been pressed
        for (int i=0; i<floors.size(); i++) {
            if (floors[i].UpPressed() || floors[i].DownPressed()) {
                // the elevator is already at the source floor
                if (floor == i) {
                    state = PROCESSING; }
                else {
                    state = MOVING;
                    (floor < i) ? UP : DOWN; } } } }

    if (state == MOVING) {
        if (!persons.empty() && Pressed(floor)) state = PROCESSING;
        else if (!floors[floor].persons.empty() && floor == floors.size()-1) {
            dir = DOWN;
            state = PROCESSING; }
        else if (!floors[floor].persons.empty() && floor == 0) {
            dir = UP;
            state = PROCESSING; }
        else if (dir == UP && !floors[floor].persons.empty() && floors[floor].UpPressed()) state = PROCESSING;
        else if (dir == DOWN && !floors[floor].persons.empty() && floors[floor].DownPressed()) state = PROCESSING;
        else {
            if (floor == 0) {
                dir = UP;
                floor++; }
            else if (floor == floors.size()-1) {
                dir = DOWN;
                floor--; }
            else {
                if (dir == UP) floor++;
                else floor--; } } }
    
    if (state == CLOSED) {
        state = MOVING;
        if (dir == UP) {
            if (floor == floors.size()-1) {
                dir = DOWN;
                floor--; }
            else floor++; }
        else {
            if (floor == 0) {
                dir = UP;
                floor++; }
            else floor--; } }

    if (state == PROCESSING) {
        if (!persons.empty()) {
            disembark(floor, iter, allpersons); }
        if (!floors[floor].persons.empty()) {
            embark(floors[floor], iter); }
        state = CLOSED;
        if (floor == floors.size()-1) dir = DOWN;
        if (floor == 0) dir = UP; }

    /*if (persons.empty()) {
        int j=0;
        for (int i=0; i<floors.size(); i++) {
            if (floors[i].persons.empty()) j++; }
        if (j == floors.size()) state == IDLE; }*/
}

void Car::embark(Floor& floor, int iter)
{
    //for (int i=0; i<floor.persons.size(); i++) {
    vector<Person>::iterator i = floor.persons.begin();
    while (i != floor.persons.end() && persons.size() < capacity) {
        if ((*i).dir() == dir) {
            cout << "> PERSON " << (*i).id << " embarking from Floor " << floor.id << " to CAR" << id << " at Time " << iter << endl;
            (*i).setEmbarkTime(iter);
            AddPerson((*i));
            Press((*i).dest);
            floor.RemovePerson((*i)); }
        else i++; }

    if (dir == UP) floor.ClearUp();
    else floor.ClearDown();
}

void Car::disembark(Floor floor, int iter, vector<Person>& allpersons)
{
    //for (int i=0; i<persons.size(); i++) {
    vector<Person>::iterator i = persons.begin();
    while (i != persons.end()) {
        if ((*i).dest == floor.id) {
            cout << "> PERSON " << (*i).id << " disembarking from CAR" << id << " to Floor " << floor.id << " at Time " << iter << endl;
            (*i).setArriveTime(iter);
            allpersons.push_back((*i));
            RemovePerson((*i)); }
        else i++; }

    Reset(floor.id); // the floor's ID is basically its index
}
