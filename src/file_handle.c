#include <stdio.h>
#include <stdint.h>
#include "file_handle.h"
#include "buffer.h"
#include "byte_processing.h"

int process_test_file(const char *path, CircularBuffer *cb, Frame *frame) {
    FILE *fp = fopen(path, "r");
    unsigned int value;
    ParserStatus ret;

    
    
    if (fp == NULL) {
        printf("Cannot open file\n");
        return -1;
    }

    while (fscanf(fp, "%2x", &value) == 1) {
        uint8_t byte = (uint8_t)value;

        if (cb_push(cb, byte) != 0) {
            printf("[ERROR] Buffer full\n");
            fclose(fp);
            return -1;
        }

        while (1) {
            ret = detect_parser_frame(cb, frame);
           
            if (ret == PARSER_OK) {
                printf("Frame OK: H = %02X LEN = %u ", frame->header, frame->len);
                    for (int i = 0; i < frame->len; i++) {
                        printf("%02X ",  frame->data[i]);
                    }
                printf("CRC = %02X\n", frame->crc);
                continue;
            }
            
            if (ret == PARSER_WAIT) {
                break;
            }

            if (ret == PARSER_RESYNC) {
                printf("[RESYNC] Dropped invalid byte\n");
                continue;
            }

            if (ret == PARSER_CRC_ERROR) {
                printf("[ERROR] CRC mismatch\n");
                continue;
            }

            if (ret == PARSER_LEN_ERROR) {
                printf("[ERROR] Invalid length\n");
                continue;
            }

            if (ret == PARSER_BUFFER_ERROR || ret == PARSER_ARG_ERROR) {
                printf("[ERROR] Fatal parser error\n");
                fclose(fp);
                return -1;
            }
        }
    }

    return 0;
}





 // switch (ret) {
            //     case PARSER_OK:
            //         break;

            //     case PARSER_WAIT:
            //         break;

            //     case PARSER_RESYNC:
            //         printf("[RESYNC] Invalid header byte, dropped 1 byte\n");
            //         break;

            //     case PARSER_CRC_ERROR:
            //         printf("[ERROR] CRC mismatch\n");
            //         break;

            //     case PARSER_LEN_ERROR:
            //         printf("[ERROR] Length too large\n");
            //         break;

            //     case PARSER_BUFFER_ERROR:
            //         printf("[ERROR] Buffer operation failed\n");
            //         break;

            //     case PARSER_ARG_ERROR:
            //         printf("[ERROR] Invalid parser arguments\n");
            //         return -1;
            // }