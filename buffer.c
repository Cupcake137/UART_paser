#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "buffer.h"

void cb_init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int cb_push(CircularBuffer *cb, uint8_t data) {
    if(cb->count == BUFFER_SIZE) {
        return -1; // Buffer is full
    }

    cb->buff[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count++;
    return 0; // Success
}

int cb_pop(CircularBuffer *cb, uint8_t *data) {
    if(cb->count == 0) {
        return -1; // Buffer is empty
    }

    *data = cb->buff[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count--;
    return 0; // Success
}

// int cb_peek(CircuarBuffer *cb, int i, uint8_t *data) {
//     if(i < 0 || i >= cb->count) {
//         return -1; // Index out of bounds
//     }
//     *data = cb->buff[cb->tail];
//     return 0; // Success
// }

int cb_peek(CircularBuffer *cb, int index, uint8_t *data) {
    if(index < 0 || index >= cb->count) {
        return -1; // Index out of bounds
    }
    int pos = (cb->tail + index) % BUFFER_SIZE;
    *data = cb->buff[pos];
    return 0; // Success
}
