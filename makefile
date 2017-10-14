exec: main.o
	g++ main.o -o exec -lpthread

main.o: main.cpp
	g++ -c main.cpp 