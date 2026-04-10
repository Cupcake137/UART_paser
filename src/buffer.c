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

    cb_debug_print_action(cb, "push", data);

    return 0; // Success
}

int cb_pop(CircularBuffer *cb, uint8_t *data) {
    if(cb->count == 0) {
        return -1; // Buffer is empty
    }

    *data = cb->buff[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count--;

    cb_debug_print_action(cb, "pop", *data);

    return 0; // Success
}

int cb_peek(CircularBuffer *cb, int index, uint8_t *data) {
    if(index < 0 || index >= cb->count) {
        return -1; // Index out of bounds
    }
    int pos = (cb->tail + index) % BUFFER_SIZE;
    *data = cb->buff[pos];
    return 0; // Success
}

void cb_debug_print_action(const CircularBuffer *cb, const char *action, uint8_t byte) {
    if (cb == NULL) {
        printf("[%s] buffer = NULL\n", action);
        return;
    }

    printf("[%s %02X] count=%d head=%d tail=%d | data: ", action, byte, cb->count, cb->head, cb->tail);

    for (int i = 0; i < cb->count; i++) {
        int pos = (cb->tail + i) % BUFFER_SIZE;
        printf("%02X ", cb->buff[pos]);
    }

    printf("\n");
}

// void cb_debug_print(const CircularBuffer *cb, const char *label) {
//     if (cb == NULL) {
//         printf("[%s] buffer = NULL\n", label);
//         return;
//     }

//     printf("[%s] count=%d head=%d tail=%d | data: ",
//            label, cb->count, cb->head, cb->tail);

//     for (int i = 0; i < cb->count; i++) {
//         int pos = (cb->tail + i) % BUFFER_SIZE;
//         printf("%02X ", cb->buff[pos]);
//     }

//     printf("\n");
// }
