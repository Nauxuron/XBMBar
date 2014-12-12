CC      = gcc
CFLAGS  = -pedantic -Wall -Wextra -std=c99
CDFLAGS = -g
SRC     = xbmbar.c
TARGET  = xbmbar

all: compile

debug: CFLAGS += $(CDFLAGS)
debug: compile

compile:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all debug compile clean
