CFLAGS = `sdl2-config --cflags` -O4 -Wall -Wextra -Wfloat-equal -pedantic -std=c89 -lm
INCS = neillsdl2.h
TARGET = hufSDL
SOURCES =  neillsdl2.c $(TARGET).c
LIBS =  `sdl2-config --libs`
CC = gcc
FILE = prideprejudice.txt

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) $(FILE)
