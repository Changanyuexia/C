CFLAGS = `sdl2-config --cflags` -O4 -Wall -Wextra -Wfloat-equal -pedantic -std=c89 -lm
INCS = eowl_english_words.txt
TARGET = tKiller2
SOURCES = $(TARGET).c
LIBS =  `sdl2-config --libs`
CC = gcc
WORD = compiler

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) $(WORD)

debug:
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) -g
debugrun:
	valgrind ./$(TARGET) $(WORD)
