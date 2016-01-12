PFLAGS = `sdl2-config --cflags` `pkg-config --cflags opencv`
CFLAGS = -O4 -Wall -Wextra -Wfloat-equal -ansi -lm -pedantic
INCS = neillsdl2.h test.h $(TARGET).h
TARGET = teletext
TARGET2 = Photo2Font
SOURCES =  neillsdl2.c test.c $(TARGET)3.c
LIBS =  `sdl2-config --libs` `pkg-config --libs opencv`
CC = gcc
C++= g++
FILE = test.m7
FILE2 = letter
FILE3 = touched
all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(PFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) $(FILE)
photo:
	g++ $(TARGET2).c -o $(TARGET2) $(CFLAGS) $(PFLAGS) $(LIBS)
runP:
	./$(TARGET2) $(FILE2) $(FILE3)
