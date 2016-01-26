PFLAGS = `sdl2-config --cflags` `pkg-config --cflags opencv`
CFLAGS = -O2 -Wall -Wextra -Wfloat-equal -ansi -lm -pedantic
INCS = neillsdl2.h $(TARGET).h
TARGET = teletext
FONT  = Photo2Font
PHOTO = Photo2Code
SOURCES =  neillsdl2.c test.c $(TARGET)4.c
LIBS =  `sdl2-config --libs` `pkg-config --libs opencv`
CC    = gcc
CPLUS = g++
FILE = test.m7
FILEFONT = letter
FILEPHOTO = bike.jpg
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
	./$(PHOTO) $(FILEPHOTO)

font:  $(FONT).c
	$(CPLUS) $(FONT).c -o $(FONT) $(CFLAGS) $(PFLAGS) $(LIBS)
runF:
		./$(FONT) $(FILEFONT)
