all: elevator

elevator: elevator.o person.o container.o building.o
	g++ -o elevator elevator.o person.o container.o building.o

elevator.o: elevator.cpp person.hpp container.hpp building.hpp
	g++ -std=c++11 -c elevator.cpp

person: person.cpp person.hpp
	g++ -c person.cpp

container: container.cpp container.hpp
	g++ -c container.cpp

building: building.cpp building.hpp
	g++ -c building.cpp