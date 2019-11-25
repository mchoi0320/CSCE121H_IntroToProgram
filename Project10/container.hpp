#include <vector>
#include <string>
using namespace std;

class Container {
    public:
        vector<bool> buttons; // true means pressed
        vector<Person> persons;

    public:
        friend class Building;
        void Press(int f);
        bool Pressed(int f);
        void Reset(int f);  
        void AddPerson(Person p);
        void RemovePerson(Person p);
};

class Floor : public Container {
    public:
        int id; // floor's index

    public:
        Floor(int i); // pass-in id; initialize 2 buttons to false
        bool UpPressed();
        bool DownPressed();
        void PressUp();
        void PressDown();
        void ClearUp();
        void ClearDown();
        void printContents();
        //vector<Person> get_persons() { return persons; }
};

class Car : public Container {
    public:
        int id; // car's index; set in constructor
        int floor; // start on a random floor
        int capacity; // don't let more than this many poeple on (=10)
        enum State { IDLE, MOVING, CLOSED, PROCESSING /*OPENING, CLOSING, LOADING, UNLOADING*/ }; // whatever states you want
        State state;
        Dir dir; // what direction is car moving?
        int nfloors;

    public:
        friend class Building;
        Car(int i, int f); // initialize with id and number of floors; initilize state, dir, and buttons
        void printContents();
        void printSymbolic(); // print something like "CAR0[3]^"
        // this is where all the logic goes...
        void update(vector<Floor>& floors, int iter, vector<Person>& allpersons); // *****
        // it is important to get these functions right...
        void embark(Floor& floor, int iter);
        void disembark(Floor floor, int iter, vector<Person>& allpersons);


};
