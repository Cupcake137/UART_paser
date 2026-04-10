#include <stdio.h>
#include <stdint.h>

#include "buffer.h"
#include "byte_processing.h"
#include "file_handle.h"

// uint8_t stream_1[] = {0xAA, 0x03, 0x10, 0x20, 0x30, 0x00}; // Example byte stream
// uint8_t stream_2[] = {0xAA, 0x02, 0x40, 0x50, 0x90}; // Another example byte stream 
// uint8_t stream_3[] = {0xAB, 0x01, 0x60, 0x60}; // Invalid header example

int main(void) {
    CircularBuffer cb;
    Frame frame;

    cb_init(&cb);

    //open test file
    process_test_file("./test/stream_test.txt", &cb, &frame);
    
    // Push some data into the buffer
    // for (int i = 0; i < sizeof(stream_1); i++) {
    //     if (cb_push(&cb, stream_1[i]) != 0) {
    //         printf("Buffer is full, cannot push byte: %d\n", stream_1[i]);
    //     }
    // }

    // Peek at the first 5 elements
    // printf("Peeking at buffer:\n");
    // for(int i = 0; i < sizeof(cb); i++) {
    //     //uint8_t data;
    //     if(cb_peek(&cb, i, &frame.data[i]) == 0) {
    //         printf("Index %d: %d\n", i, frame.data[i]);
    //     } else {
    //         printf("Index %d: Out of bounds\n", i);
    //     }
    // }
    
    // if (detect_parser_frame(&cb, &frame) == 1) {
    //     printf("Frame detected successfully.\n");

    //      // Pop all elements from the buffer
    //     // printf("\nPopping from buffer:\n");
    //     // uint8_t data;
    //     // while(cb_pop(&cb, &frame_data.data[0]) == 0) {
    //     //     printf("Popped: %hhn\n", frame_data.data[0]);
    //     // }
    // } else {
    //     printf("No valid frame detected.\n");
    // }

    return 0;
}
