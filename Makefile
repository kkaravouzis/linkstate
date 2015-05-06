# Using g++ compliler
# suppressing compiler warnings
CC=g++
CFLAGS=-g -DDEBUG
SOURCES=main.cpp
OBJ = main.o
TARGET=linkstate

all: $(TARGET)
$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET)

debug: 
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

.PHONY: clean

clean:
	rm $(TARGET)