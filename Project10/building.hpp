class Building {
    public:
        int ITERS;
        int nfloors;
        int ncars;

        vector<Floor> floors;
        vector<Car> cars;
        vector<Person> persons;

    public:
        void AddPerson(Person p);
        void RemovePerson(Person p);
        void readin_traffic(char* fname);
        Building(int numiters, int numfloors, int numcars, char* fname);
        void NewArrivals(int iter); // check for person whose start time has arrived
        void summary(); // print-out all persons, cars, and floors at end
        void run();
};
