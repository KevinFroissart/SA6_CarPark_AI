WRAPPER=$(if $(shell which clang++), clang++, g++)
CPP=$(WRAPPER)
LD=$(WRAPPER)
CFLAGS=-Wall -W -Werror -g

LDFLAGS =
LIBS = plantuml.jar*
LBLIBS = -lsfml-graphics -lsfml-window -lsfml-system
THREAD = -std=c++11 -pthread

EXE=sa6.out
DOX=doc/Doxyfile

TARGET=bin/
CPATH=src/
HPATH=header/
DOC=doc/

HEADERS=$(wildcard $(HPATH)*.hpp)
SOURCES=$(wildcard $(CPATH)*.cpp)
OBJECTS = $(foreach source, $(SOURCES), obj/$(patsubst src/%.cpp,%.o,$(source)))
BINARY = bin/$(EXE)

.PHONY: all clean mrproper rebuild run doc cleandoc uml

all: $(BINARY)

doc: uml
	@doxygen $(DOX)

uml:
	java -jar $(DOC)$(LIBS) $(DOC)?*.plantuml 

cleandoc:
	$(RM) -Rf $(DOC)html $(DOC)rtf $(DOC)SA6_uml.png
	#find $(DOC) -type f ! -name '*.info' -delete

clean: 
	$(RM) $(OBJECTS) 
	$(RM) makefile.dep 
	$(RM) obj/?*.o # catch all renamed files
	
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
	$(LD) $(LDFLAGS) $(THREAD) -o $@ $^ $(LBLIBS)

obj/%.o: src/%.cpp
	$(CPP) $(CFLAGS) -o $@ -c $<
	
include makefile.dep