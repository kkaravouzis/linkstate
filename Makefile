# Using g++ compliler
# suppressing compiler warnings
CC=g++
CFLAGS=-O3
SOURCES=main.cpp
OBJ = main.o
TARGET=linkstate

all: $(TARGET)
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

debug: 
	$(CC) $(CFLAGS) -g -DDEBUG $(SOURCES) -o $(TARGET)

.PHONY: clean

clean:
	rm $(TARGET)