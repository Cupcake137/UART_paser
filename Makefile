CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = test_uart
SRCS = main.c buffer.c byte_processing.c
OBJS = $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c buffer.h byte_processing.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	.\$(TARGET)

clean:
	cmd /C del /Q $(OBJS) $(TARGET).exe 2>nul || exit 0
