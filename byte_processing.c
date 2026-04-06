#include <stdio.h>
#include <stdint.h>
#include "buffer.h"
#include "byte_processing.h"

CircularBuffer cb;

void process_byte(uint8_t byte) {
    cb_push(&cb, byte);
}

int detect_parser_frame(CircularBuffer *cb, uint8_t *frame_data) {
    if(cb->count < 5) {
        return -1; // Not enough data for a frame
    }

    if(cb->buff[cb->tail] == 0xAA) { // Start byte
        int frame_length = cb->buff[(cb->tail + 1) % BUFFER_SIZE]; // Length byte
        if(frame_length > 0 && frame_length <= 3) { // Valid length
            for(int i = 0; i < frame_length; i++) {
                frame_data[i] = cb->buff[(cb->tail + 2 + i) % BUFFER_SIZE]; // Data bytes
            }
            return frame_length; // Return the length of the frame data
        }
    } else {
        // If the start byte is not found, pop the byte to move forward
        uint8_t temp;
        cb_pop(cb, &temp);
    }
    return -1; // No valid frame found

    uint8_t checksum_index = (cb->tail + 2 + frame_length) % BUFFER_SIZE;
    if (checksum_index < BUFFER_SIZE) {
        uint8_t checksum = cb->buff[checksum_index];
        uint8_t calculated_checksum = 0;
        for(int i = 0; i < frame_length; i++) {
            calculated_checksum += frame_data[i];
        }
        if(calculated_checksum == checksum) {
            return frame_length; // Valid frame with correct checksum
        }
    }
    return -1; // Invalid frame or checksum

    //parse frame and validate checksum
    
}