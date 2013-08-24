CC=g++
CFLAGS=-c -Wall
LDFLAGS=-L/usr/lib -lpthread -lboost_system
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cms

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXECUTABLE)
