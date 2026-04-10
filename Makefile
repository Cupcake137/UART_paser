CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11 -Iinc
TARGET = uart_parser

SRCS = src/main.c src/buffer.c src/byte_processing.c src/file_handle.c src/logger.c
OBJS = $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
