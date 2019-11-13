all: keywords iriscorr HourlyRotation poly cities genomics NewtonRaphsonSqrt subsetsI subsetsR vending histogram calendar

keywords: keywords.o char_check.o
	g++ -o keywords keywords.o char_check.o

keywords.o: keywords.cpp char_check.hpp
	g++ -std=c++11 -c keywords.cpp

char_check: char_check.cpp char_check.hpp
	g++ -c char_check.cpp

iriscorr: iriscorr.o matrix.o
	g++ -o iriscorr iriscorr.o matrix.o

iriscorr.o: iriscorr.cpp matrix.hpp
	g++ -c iriscorr.cpp

HourlyRotation: HourlyRotation.cpp
	g++ -o HourlyRotation HourlyRotation.cpp

matrix: matrix.cpp matrix.hpp
	g++ -c matrix.cpp

poly: poly.o poly_class.o print_vec.o
	g++ -o poly poly.o poly_class.o print_vec.o

poly.o: poly.cpp poly_class.hpp print_vec.hpp
	g++ -std=c++11 -c poly.cpp

poly_class: poly_class.cpp poly_class.hpp
	g++ -std=c++11 -c poly_class.cpp

print_vec: print_vec.cpp print_vec.hpp
	g++ -c print_vec.cpp

cities: cities.cpp
	g++ -std=c++11 -o cities cities.cpp

genomics: genomics.o codons.o
	g++ -o genomics genomics.o codons.o

genomics.o: genomics.cpp codons.hpp
	g++ -std=c++11 -c genomics.cpp

codons: codons.cpp codons.hpp
	g++ -c codons.cpp

NewtonRaphsonSqrt: NewtonRaphsonSqrt.cpp
	g++ -o NewtonRaphsonSqrt NewtonRaphsonSqrt.cpp

subsetsI: subsetsI.cpp
	g++ -std=c++11 -o subsetsI subsetsI.cpp

subsetsR: subsetsR.cpp
	g++ -std=c++11 -o subsetsR subsetsR.cpp

vending: vending.cpp
	g++ -std=c++11 -o vending vending.cpp

histogram: histogram.cpp
	g++ -o histogram histogram.cpp

calendar: calendar.cpp
	g++ -o calendar calendar.cpp
