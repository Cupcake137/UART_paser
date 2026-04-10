#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#define BUFFER_SIZE 64

typedef struct {
    uint8_t buff[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

void cb_init(CircularBuffer *cb);
int cb_push(CircularBuffer *cb, uint8_t data);
int cb_pop(CircularBuffer *cb, uint8_t *data);
int cb_peek(CircularBuffer *cb, int index, uint8_t *data);
//void cb_debug_print(const CircularBuffer *cb, const char *label);
void cb_debug_print_action(const CircularBuffer *cb, const char *action, uint8_t byte);

#endif // BUFFER_H
