WRAPPER=$(if $(shell which clang++), clang++, g++)
CPP=$(WRAPPER)
LD=$(WRAPPER)
CFLAGS=-Wall -W -Werror -g

LDFLAGS =
LIBS =

EXE=sa6.out

TARGET=bin/
CPATH=src/
HPATH=header/

HEADERS=$(wildcard $(HPATH)*.h)
SOURCES=$(wildcard $(CPATH)*.cpp)
OBJECTS = $(foreach source, $(SOURCES), obj/$(patsubst src/%.cpp,%.o,$(source)))
BINARY = bin/$(EXE)

.PHONY: all clean mrproper rebuild run

all: $(BINARY)

clean: 
	$(RM) $(OBJECTS) 
	$(RM) Makefile.dep 
	$(RM) obj/?*.* # catch all renamed files
	
mrproper: clean 
	$(RM) $(BINARY) 

rebuild: 
	@make mrproper
	@make
	
run: all
	./$(BINARY) 
	
makefile.dep: $(SOURCES) $(HEADERS)
	@echo "Calculating dependencies"
	@$(RM) makefile.dep
	@for file in $(SOURCES); do echo "obj/`g++ $(CFLAGS) -MM $$file`" >> makefile.dep; done

$(BINARY): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

obj/%.o: src/%.cpp
	$(CPP) $(CFLAGS) -o $@ -c $<
	
include makefile.dep