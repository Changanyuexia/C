PFLAGS = `sdl2-config --cflags` `pkg-config --cflags opencv`
CFLAGS = -O2 -Wall -Wextra -Wfloat-equal -ansi -lm -pedantic
INCS = neillsdl2.h test.h $(TARGET).h
TARGET = teletext
TARGET2 = Photo2Font
TARGET3 = Photo2Code
SOURCES =  neillsdl2.c test.c $(TARGET)4.c
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
photo:  $(TARGET3).c
	g++ $(TARGET3).c -o $(TARGET3) $(CFLAGS) $(PFLAGS) $(LIBS)
runP:
	./$(TARGET3) $(FILE2) $(FILE3)
