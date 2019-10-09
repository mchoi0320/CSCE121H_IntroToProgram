all: genomics mysplit NewtonRaphsonSqrt subsetsI subsetsR pi randomize iris pointers geometry arrays vending histogram hello hello2 examples showbits area area2 circle stringtest1 stringtest2 show_words weather calendar gcd fact fib

genomics: genomics.cpp
	g++ -o genomics genomics.cpp

mysplit: mysplit.cpp
	g++ -o mysplit mysplit.cpp

NewtonRaphsonSqrt: NewtonRaphsonSqrt.cpp
	g++ -o NewtonRaphsonSqrt NewtonRaphsonSqrt.cpp

subsetsI: subsetsI.cpp
	g++ -o subsetsI subsetsI.cpp

subsetsR: subsetsR.cpp
	g++ -o subsetsR subsetsR.cpp

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
	g++ --std=c++11 -o vending vending.cpp

histogram: histogram.cpp
	g++ -o histogram histogram.cpp

fib: fib.cpp
	g++ -o fib fib.cpp

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
