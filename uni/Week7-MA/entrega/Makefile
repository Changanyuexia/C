CFLAGS     =  -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm
SDLFLAGS   = `sdl2-config --cflags`
TARGET     = wordladder
DICTIONARY = eowl_english_words.txt
SOURCES    = $(TARGET).c
LIBS       =  `sdl2-config --libs`
CC         = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS) $(SDLFLAGS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) $(DICTIONARY)
freed: wordladderfreed.c Makefile
	$(CC) wordladderfreed.c -o freed $(CFLAGS) -g
