#include <iostream>
#include <cstdlib>
#include "person.hpp"
#include "container.hpp"
#include "building.hpp"
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 5) {
        cout << "\nPlease enter command-line arguments in the following format:\n\n";
        cout << "\t./elevator <number of iterations> <number of floors> <number of cars> <traffic file>\n\n";
        exit(0); }


    int numTimesteps = atoi(argv[1]);
    int numFloors = atoi(argv[2]);
    int numCars = atoi(argv[3]);
    char* trafficFile = argv[4];
    

    srand(time(NULL));
    Building building(numTimesteps, numFloors, numCars, trafficFile);
    building.run();
    building.summary();
}