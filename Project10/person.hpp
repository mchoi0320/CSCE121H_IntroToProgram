enum Dir { DOWN=0, UP=1 };

class Person {
    public:
        int id;
        int start;      // time when arrives at source floor
        int src;        // source floor
        int dest;       // destination floor
        int embarkTime; // boarding car
        int arriveTime; // arriving at destination floor

    public:
        friend class Building;
        Person(int i, int t, int s, int d);   // constuctor: pass-in id, time, src, dest
        //bool operator==(const Person& p);
        //bool operator<(const Person& p);
        friend bool operator==(const Person& p1, const Person& p2);     // based on id, to check if 2 persons are same
        friend bool operator<(const Person& p1, const Person& p2);      // based on start time, for sorting
        void setEmbarkTime(int x);
        void setArriveTime(int x);
        Dir dir(); // what direction are they travelling?
        void print();
};

bool operator==(const Person& p1, const Person& p2);
bool operator<(const Person& p1, const Person& p2);
