# Makefile for process_counter

CC = gcc
CFLAGS = -Wall -O2
TARGET = process_counter

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c -lm

clean:
	rm -f $(TARGET)
