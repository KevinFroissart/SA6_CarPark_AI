WRAPPER=$(if $(shell which clang++), clang++, g++)
CC=$(WRAPPER)
CFLAGS=-Wall -W -Werror -g

EXE=sa6.out

HEADERS=$(wildcard *.h)
CFILES=$(wildcard *.cpp)
OBJS=$(CFILES:.cpp=.o)

.PHONY: all clean mrproper

all: $(EXE)

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

makefile.dep: $(CFILES) $(HEADERS)
	$(CC) -MM $(CFILES) > $@

clean: 
	$(RM) $(OBJS) makefile.dep

mrproper : clean
	$(RM) $(EXE)

include makefile.dep