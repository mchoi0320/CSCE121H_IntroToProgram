all: hello hello2 examples showbits area area2 circle stringtest1 stringtest2 show_words weather calendar gcd fact fib

fib: fib.cpp
	g++ -o fib fib.cpp

fact: fact.cpp
	g++ -o fact fact.cpp

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
