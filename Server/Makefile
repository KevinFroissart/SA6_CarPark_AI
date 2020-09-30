WRAPPER=$(if $(shell which clang++), clang++, g++)
CC=$(WRAPPER)
CFLAGS=-Wall -W -Werror -g

EXE=client.out
EXEs=server.out

.PHONY: all clean mrproper

all: $(EXE) $(EXEs)

$(EXE) : Main.o Sockets.o TCPSocket.o
	$(CC) $(CFLAGS) Main.o Sockets.o TCPSocket.o -o $@

$(EXEs) : MainServeur.o
	$(CC) $(CFLAGS) MainServeur.o -o $@

MainServeur.o : MainServeur.cpp
	$(CC) $(CFLAGS) -c MainServeur.cpp

Main.o : Main.cpp
	$(CC) $(CFLAGS) -c Main.cpp

Sockets.o : Sockets.cpp
	$(CC) $(CFLAGS) -c Sockets.cpp

TCPSocket.o : TCPSocket.cpp	
	$(CC) $(CFLAGS) -c TCPSocket.cpp

clean: 
	$(RM) *.o

mrproper : clean
	$(RM) *.out