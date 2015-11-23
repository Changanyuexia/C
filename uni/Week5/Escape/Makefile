CFLAGS = `sdl2-config --cflags` -O4 -Wall -Wextra -Wfloat-equal -pedantic -std=c89 -lm
INCS = neillsdl2.h
TARGET = maze
SOURCES = $(TARGET).c
LIBS =  `sdl2-config --libs`
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) 
