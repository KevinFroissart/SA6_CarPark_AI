WRAPPER=$(if $(shell which clang++), clang++, g++)
CC=$(WRAPPER)
CFLAGS=-Wall -W -Werror -g

EXE=client.out
EXEs=server.out

.PHONY: all clean mrproper

all: $(EXE) $(EXEs)

$(EXE) : Main.o Sockets.o TCPSocket.o
	$(CC) $(CFLAGS) Main.o Sockets.o TCPSocket.o -o bin/$@

$(EXEs) : MainServeur.o ServerParking.o
	$(CC) $(CFLAGS) MainServeur.o ServerParking.o -o bin/$@

MainServeur.o : src/MainServeur.cpp
	$(CC) $(CFLAGS) -c src/MainServeur.cpp

ServerParking.o : src/ServerParking.cpp
	$(CC) $(CFLAGS) -c src/ServerParking.cpp

Main.o : src/Main.cpp
	$(CC) $(CFLAGS) -c src/Main.cpp

Sockets.o : src/Sockets.cpp
	$(CC) $(CFLAGS) -c src/Sockets.cpp

TCPSocket.o : src/TCPSocket.cpp	
	$(CC) $(CFLAGS) -c src/TCPSocket.cpp

clean: 
	$(RM) *.o

mrproper : clean
	$(RM) bin/*.out