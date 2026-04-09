#include <stdio.h>
#include <stdint.h>
#include "file_handle.h"

void open_test_file(void) {
    size_t ret;
    unsigned char buffer[64];
    unsigned int value;

    FILE* filePath = fopen("./test/stream_test.txt", "r");

    if (filePath == NULL) {
        printf("Cannot open file!!!\n");
        return;
    } else{
        printf("Open file successful!!!\n");
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

    while (fscanf(filePath, "%2x", &value) == 1) {
        printf("0x%02X\n", value & 0xFF);
    }

    fclose(filePath);
}

void read_test_file(void) {
    
}