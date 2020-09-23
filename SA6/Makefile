WRAPPER=g++
CC=$(WRAPPER)
CFLAGS=-Wall -W -Werror -g

EXE=sa6.out

#Pour améliorer le makefile à l'avenir
HEADERS=$(wildcard *.h)
CFILES=$(wildcard *.c)
OBJS=$(CFILES:.c=.o)

.PHONY: all clean mrproper

all: $(EXE)

$(EXE) : main.o voiture.o parking.o CSVManager.o
	$(CC) $(CFLAGS) main.o voiture.o parking.o CSVManager.o -o $@

main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

CSVManager.o : CSVManager.cpp
	$(CC) $(CFLAGS) -c CSVManager.cpp

voiture.o : voiture.cpp
	$(CC) $(CFLAGS) -c voiture.cpp

parking.o : parking.cpp
	$(CC) $(CFLAGS) -c parking.cpp

clean: 
	$(RM) *.o

mrproper : clean
	$(RM) $(EXE)
	