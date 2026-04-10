#ifndef BYTE_PROCESSING_H
#define BYTE_PROCESSING_H

#include <stdint.h>

typedef struct {
    uint8_t header;
    uint8_t len;
    uint8_t data[16];
    uint8_t crc;
} Frame;

//void process_byte(uint8_t byte);
int detect_parser_frame(CircularBuffer *cb, Frame *frame);

#endif // BYTE_PROCESSING_H