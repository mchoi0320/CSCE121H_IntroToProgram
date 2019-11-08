all: iriscorr HourlyRotation tuple_practice testvec poly cities genomics mysplit NewtonRaphsonSqrt subsetsI subsetsR pi randomize iris pointers geometry arrays vending histogram hello hello2 examples showbits area area2 circle stringtest1 stringtest2 show_words weather calendar gcd fact fib fibDP

iriscorr: iriscorr.o matrix.o
	g++ -o iriscorr iriscorr.o matrix.o

iriscorr.o: iriscorr.cpp matrix.hpp
	g++ -std=c++11 -c iriscorr.cpp

HourlyRotation: HourlyRotation.cpp
	g++ -o HourlyRotation HourlyRotation.cpp

matrix: matrix.cpp matrix.hpp
	g++ -c matrix.cpp

tuple_practice: tuple_practice.cpp
	g++ -o tuple_practice tuple_practice.cpp

testvec: testvec.o myvec.o
	g++ -o testvec testvec.o myvec.o

testvec.o: testvec.cpp myvec.hpp
	g++ -c testvec.cpp

myvec: myvec.cpp myvec.hpp
	g++ -c myvec.cpp

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

mysplit: mysplit.cpp
	g++ -o mysplit mysplit.cpp

NewtonRaphsonSqrt: NewtonRaphsonSqrt.cpp
	g++ -o NewtonRaphsonSqrt NewtonRaphsonSqrt.cpp

subsetsI: subsetsI.cpp
	g++ -std=c++11 -o subsetsI subsetsI.cpp

subsetsR: subsetsR.cpp
	g++ -std=c++11 -o subsetsR subsetsR.cpp

pi: pi.cpp
	g++ -o pi pi.cpp

randomize: randomize.cpp
	g++ -o randomize randomize.cpp

iris: iris.cpp
	g++ --std=c++11 -o iris iris.cpp

pointers: pointers.cpp
	g++ -o pointers pointers.cpp

geometry: geometry.cpp
	g++ -o geometry geometry.cpp

arrays: arrays.cpp
	g++ -o arrays arrays.cpp

vending: vending.cpp
	g++ -std=c++11 -o vending vending.cpp

histogram: histogram.cpp
	g++ -o histogram histogram.cpp

fib: fib.cpp
	g++ -o fib fib.cpp

fibDP: fibDP.cpp
	g++ -std=c++11 -o fibDP fibDP.cpp

fact: fact.o fact_utils.o
	g++ -o fact fact.o fact_utils.o

fact.o: fact.cpp fact_utils.hpp
	g++ -c fact.cpp

fact_utils: fact_utils.cpp fact_utils.hpp
	g++ -c fact_utils.cpp

gcd: gcd.cpp
	g++ -o gcd gcd.cpp

calendar: calendar.cpp
	g++ -o calendar calendar.cpp

hello: hello.cpp
	g++ -o hello hello.cpp

hello2: hello2.c
	g++ -o hello2 hello2.c

examples: examples.cpp
	g++ -o examples examples.cpp

showbits: showbits.cpp
	g++ -o showbits showbits.cpp

area: area.cpp
	g++ -o area area.cpp

area2: area2.cpp
	g++ -o area2 area2.cpp

circle: circle.cpp
	g++ -o circle circle.cpp

stringtest1: stringtest1.c
	g++ -Wdeprecated-declarations -o stringtest1 stringtest1.c

stringtest2: stringtest2.cpp
	g++ -o stringtest2 stringtest2.cpp

show_words: show_words.cpp
	g++ -o show_words show_words.cpp

weather: weather.cpp
	g++ -o weather weather.cpp

wordcount: wordcount.cpp
	g++ -o wordcount wordcount.cpp
