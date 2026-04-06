#include <stdio.h>
#include <stdint.h>

#include "buffer.h"

uint8_t stream[] = {0xAA, 0x03, 0x10, 0x20, 0x30, 0x60}; // Example byte stream

int main() {
    CircularBuffer cb;
    cb_init(&cb);

    // Push some data into the buffer
    for (int i = 0; i < sizeof(stream); i++) {
        if (cb_push(&cb, stream[i]) != 0) {
            printf("Buffer is full, cannot push byte: %d\n", stream[i]);
        }
    }

    // Peek at the first 5 elements
    printf("Peeking at buffer:\n");
    for(int i = 0; i < sizeof(stream); i++) {
        uint8_t data;
        if(cb_peek(&cb, i, &data) == 0) {
            printf("Index %d: %d\n", i, data);
        } else {
            printf("Index %d: Out of bounds\n", i);
        }
    }

    // Pop all elements from the buffer
    printf("\nPopping from buffer:\n");
    uint8_t data;
    while(cb_pop(&cb, &data) == 0) {
        printf("Popped: %d\n", data);
    }

    return 0;
}
