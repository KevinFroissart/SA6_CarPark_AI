all : execute.out

execute.out : main.o voiture.o parking.o
	g++ -g main.o voiture.o parking.o -o execute.out


main.o : main.cpp
	g++ -g -Wall -c main.cpp

voiture.o : voiture.cpp
	g++ -g -Wall -c voiture.cpp

parking.o : parking.cpp
	g++ -g -Wall -c parking.cpp

clear: 
	rm *.o

veryclear : clear
	rm *.out