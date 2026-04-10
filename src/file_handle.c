#include <stdio.h>
#include <stdint.h>
#include "file_handle.h"
#include "buffer.h"

int file_handler(void) {
    size_t ret;
    unsigned char buffer[64];
    uint8_t byte;
    CircularBuffer *cb;    

    FILE* filePath = fopen("./test/stream_test.txt", "r");

    if (filePath == NULL) {
        printf("Cannot open file!!!\n");
        return 0;
    } else{
        printf("Open file successful!!!\n");
        return 1;
    }
    
    // ret = fread(buffer, sizeof(*buffer), 5, filePath);
    // if (ret == 0) {
    //     printf("Read file fail\n");
    // } else {
    //     printf("Read %zu bytes:\n", ret);
    //     for (size_t i = 0; i < ret; i++) {
    //         printf("0x%02X", buffer[i]);
    //     }
    //     printf("\n");
    // }

    while (fscanf(filePath, "%2x", &byte) == 1) {
        if (byte == NULL) {
            printf("Cannot read value in file\n");
            return 0;
        }
        else {
            //process_byte(byte);
            cb_push(&cb, byte);
            printf("Push stream int file into buffer successful\n");
            return 1;
        }
    }

    fclose(filePath);
}

void feed_test_stream(CircularBuffer *cb) {

}
