PFLAGS = `sdl2-config --cflags` `pkg-config --cflags opencv`
CFLAGS = -O2 -Wall -Wextra -Wfloat-equal -ansi -lm -pedantic
INCS = neillsdl2.h clauses.h $(TARGET).h
TARGET = teletext
FONT  = Photo2Font
PHOTO = Photo2Code
SOURCES =  neillsdl2.c test.c clauses.c $(TARGET).c
LIBS =  `sdl2-config --libs` `pkg-config --libs opencv`
CC    = gcc
CPLUS = g++
FILE = test.m7
FILEFONT = letter
FILEPHOTO = bike.jpg
TITLE =     "THE DIGITALIZED BIKE" #put a title to the graphics

COLGRAPHICS   =  1 #integers from 1 to 7 to choose a color

GRAPHICSMOD   = 1 # 1/0 for separeted or contiguous graphics

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(PFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)
run: all
	./$(TARGET) $(FILE)


photo:  $(PHOTO).c
	$(CPLUS) $(PHOTO).c -o $(PHOTO) $(CFLAGS) $(PFLAGS) $(LIBS)
runP:
	./$(PHOTO) $(FILEPHOTO) $(TITLE) $(COLGRAPHICS) $(GRAPHICSMOD)

font:  $(FONT).c
	$(CPLUS) $(FONT).c -o $(FONT) $(CFLAGS) $(PFLAGS) $(LIBS)
runF:
		./$(FONT) $(FILEFONT)
