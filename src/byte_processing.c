#include <stdio.h>
#include <stdint.h>
#include "buffer.h"
#include "byte_processing.h"

CircularBuffer cb;

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
        return -1; // Invalid arguments
    }

    if (cb->count < 1) {
        return 0; // Not enough data to detect frame
    }

    if (cb_peek(cb, 0, &frame_data->header) != 0) {
        return -1; // Failed to peek header 
    } // Check header byte

    //cb_peek(cb, 0, &frame_data->header);

    if (frame_data->header != 0xAA) {
        cb_pop(cb, &byte);  // Remove invalid byte
        //printf("Invalid header byte: %d\n", frame_data->header);
        return -1; // Invalid header
    }

    if (cb->count < 2) {
        return 0; // Not enough data to read length
    }

    if (cb_peek(cb, 1, &len) != 0) {
        return -1; // Failed to peek length
    }

    if (len > sizeof(frame_data->data)) {
        cb_pop(cb, &byte); // Remove header byte
        //printf("Invalid length byte: %d\n", len);
        return -1; // Invalid length
    }  

    total_frame_size = 1 + 1 + len + 1; // header + len + data + crc
    if (cb->count < total_frame_size) {
        return 0; // Not enough data to read full frame
    }

    frame_data->len = len;

    for(int i = 0; i < len; i++){
        if (cb_peek(cb, 2 + i, &frame_data->data[i]) != 0) {
            return -1; // Failed to peek data byte
        }
        crc_calculated ^= frame_data->data[i];
    }

    // cb_peek(cb, 2 + len, &frame_data->crc);
    // for(int i = 0; i < len; i++){
    //     crc_calculated ^= frame_data->data[i];
    // }

    if (cb_peek(cb, 2 + len, &frame_data->crc) != 0) {
        return -1; // Failed to peek CRC byte
    }

    if (crc_calculated != frame_data->crc) {
        cb_pop(cb, &byte); // Remove header byte
        //printf("CRC mismatch: calculated %d, expected %d\n", crc_calculated, frame_data->crc);
        return -1; // CRC mismatch
    }

    //printf("Popped: %d\n", frame_data->header);
    for (int i = 0; i < total_frame_size; i++) {
        if (cb_pop(cb, &byte) != 0) {
            return -1; // Failed to pop byte
        }
        //printf("Popped byte: %d\n", byte);
    }

    return 1; // Frame detected successfully
}