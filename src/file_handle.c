#include <stdio.h>
#include <stdint.h>
#include "file_handle.h"
#include "buffer.h"
#include "byte_processing.h"

int process_test_file(const char *path, CircularBuffer *cb, Frame *frame) {
    FILE *fp = fopen(path, "r");
    unsigned int value;
    
    if (fp == NULL) {
        printf("Cannot open file\n");
        return -1;
    }

    while (fscanf(fp, "%2x", &value) == 1) {
        uint8_t byte = (uint8_t)value;

        if (cb_push(cb, byte) != 0) {
            printf("Buffer full\n");
            fclose(fp);
            return -1;
        }

        int ret = detect_parser_frame(cb, frame);

        if (ret == 1) {
            printf("Frame OK: len = %u\n", frame->len);
        } else if (ret == -1) {
            printf("Invalid frame\n");
        }
    } 

    fclose(fp);

    return 0;
}
