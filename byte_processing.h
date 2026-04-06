#ifndef BYTE_PROCESSING_H
#define BYTE_PROCESSING_H

#include <stdint.h>


void process_byte(uint8_t byte);
int detect_parser_frame(CircularBuffer *cb, uint8_t *frame_data);

#endif // BYTE_PROCESSING_H