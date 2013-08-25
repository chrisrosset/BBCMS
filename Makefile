CC=g++
CFLAGS=-c -Wall
LDFLAGS=-L/usr/lib -lpthread -lboost_system
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cms

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) $(OBJECTS) -o bin/$@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm -f $(OBJECTS)
	-rm -f bin/$(EXECUTABLE)
