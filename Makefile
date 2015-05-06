# Using g++ compliler
# suppressing compiler warnings
CC=g++
CCFLAGS=-w
SOURCES=main.cpp
OBJ = main.o
TARGET=linkstate

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CCFLAGS) $(SOURCES) -o $(TARGET)

debug: $(TARGET)
$(TARGET): $(SOURCES)
	$(CC) $(CCFLAGS) -d DEBUG $(SOURCES) -o $(TARGET)

main.o: main.cpp
	$(CC) $(CCFLAGS) -c main.cpp
	
.PHONY: clean

clean:
	rm $(OBJ) $(TARGET)