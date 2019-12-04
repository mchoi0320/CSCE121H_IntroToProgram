all: poly

poly: poly.o poly_class.o
	g++ -o poly poly.o poly_class.o

poly.o: poly.cpp poly_class.hpp
	g++ -c poly.cpp

poly_class: poly_class.cpp poly_class.hpp
	g++ -c poly_class.cpp