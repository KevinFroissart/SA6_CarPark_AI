WRAPPER=$(if $(shell which clang++), clang++, g++)
CC=$(WRAPPER)
CFLAGS=-Wall -W -Werror -g

TARGET=bin/
CPATH=src/
HPATH=header/

HEADERS=$(wildcard $(HPATH)*.h)
CFILES=$(wildcard $(CPATH)*.cpp)
OBJS=$(CFILES:.cpp=.o)

EXE=sa6.out

.PHONY: all clean mrproper

all: $(EXE)

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)$@

makefile.dep: $(CFILES) $(HEADERS)
	$(CC) -MM $(CFILES) > $@

clean: 
	$(RM) $(OBJS) makefile.dep

mrproper : clean
	$(RM) $(TARGET)$(EXE)

include makefile.dep