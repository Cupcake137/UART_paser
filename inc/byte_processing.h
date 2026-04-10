#ifndef BYTE_PROCESSING_H
#define BYTE_PROCESSING_H

#include <stdint.h>
#include "buffer.h"

typedef enum {
    PARSER_OK = 1,
    PARSER_WAIT = 0,
    PARSER_RESYNC = -1,
    PARSER_CRC_ERROR = -2,
    PARSER_LEN_ERROR = -3,
    PARSER_BUFFER_ERROR = -4,
    PARSER_ARG_ERROR = -5
} ParserStatus;

typedef struct {
    uint8_t header;
    uint8_t len;
    uint8_t data[16];
    uint8_t crc;
} Frame;

//void process_byte(uint8_t byte);
int detect_parser_frame(CircularBuffer *cb, Frame *frame);

#endif // BYTE_PROCESSING_H