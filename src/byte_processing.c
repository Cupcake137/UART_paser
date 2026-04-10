#include <stdio.h>
#include <stdint.h>
#include "buffer.h"
#include "byte_processing.h"

// void process_byte(uint8_t byte) {
//     cb_push(&cb, byte);
// }

int detect_parser_frame(CircularBuffer *cb, Frame *frame_data) {
    //frame_data->header = 0xAA; // Set expected header value
    uint8_t byte;
    uint8_t len;
    uint8_t crc_calculated = 0;
    uint8_t total_frame_size;

    if (cb == NULL || frame_data == NULL) {
        return PARSER_ARG_ERROR; // Invalid arguments
    }

    if (cb->count < 1) {
        return PARSER_WAIT; // Not enough data to detect frame
    }

    if (cb_peek(cb, 0, &frame_data->header) != 0) {
        return PARSER_BUFFER_ERROR; // Failed to peek header 
    } // Check header byte

    if (frame_data->header != 0xAA) {
        cb_pop(cb, &byte);  // Remove invalid byte
        return PARSER_RESYNC; // Invalid header
    }

    if (cb->count < 2) {
        return PARSER_WAIT; // Not enough data to read length
    }

    if (cb_peek(cb, 1, &len) != 0) {
        return PARSER_BUFFER_ERROR; // Failed to peek length
    }

    if (len > sizeof(frame_data->data)) {
        cb_pop(cb, &byte); // Remove header byte
        return PARSER_LEN_ERROR; // Invalid length
    }  

    total_frame_size = 1 + 1 + len + 1; // header + len + data + crc
    if (cb->count < total_frame_size) {
        return PARSER_WAIT; // Not enough data to read full frame
    }

    frame_data->len = len;

    for(int i = 0; i < len; i++){
        if (cb_peek(cb, 2 + i, &frame_data->data[i]) != 0) {
            return PARSER_BUFFER_ERROR; // Failed to peek data byte
        }
        crc_calculated ^= frame_data->data[i];
    }

    if (cb_peek(cb, 2 + len, &frame_data->crc) != 0) {
        return PARSER_BUFFER_ERROR; // Failed to peek CRC byte
    }

    if (crc_calculated != frame_data->crc) {
        cb_pop(cb, &byte); // Remove header byte
        //printf("CRC mismatch: calculated %d, expected %d\n", crc_calculated, frame_data->crc);
        return PARSER_CRC_ERROR; // CRC mismatch
    }

    for (int i = 0; i < total_frame_size; i++) {
        if (cb_pop(cb, &byte) != 0) {
            return PARSER_BUFFER_ERROR; // Failed to pop byte
        }
    }

    return PARSER_OK; // Frame detected successfully
}