#include <stdio.h>
#include <stdint.h>

#include "file_handle.h"
#include "buffer.h"
#include "byte_processing.h"
#include "logger.h"

static void print_frame(const Frame *frame)
{
    if (frame == NULL) {
        return;
    }

    printf("Frame OK: H = %02X LEN = %u ", frame->header, frame->len);
    for (uint8_t i = 0; i < frame->len; i++) {
        printf("%02X ", frame->data[i]);
    }
    printf("CRC = %02X\n", frame->crc);
}

int process_test_file(const char *path, CircularBuffer *cb, Frame *frame) {
    FILE *fp = NULL;
    unsigned int value = 0;

    if (path == NULL || cb == NULL || frame == NULL) {
        logger_write(LOG_ERROR, "process_test_file: invalid argument");
        return -1;
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        logger_write(LOG_ERROR, "Cannot open file: %s", path);
        return -1;
    }

    logger_write(LOG_INFO, "Start processing file: %s", path);

    while (fscanf(fp, "%2x", &value) == 1) {
        uint8_t byte = (uint8_t)value;

        if (cb_push(cb, byte) != 0) {
            logger_write(LOG_ERROR, "Buffer full while pushing byte: %02X", byte);
            fclose(fp);
            return -1;
        }

        logger_write(LOG_INFO, "Read byte: %02X", byte);

        while (1) {
            ParserStatus ret = detect_parser_frame(cb, frame);

            switch (ret) {
                case PARSER_OK:
                    print_frame(frame);
                    logger_write(LOG_INFO, "Frame OK: H=%02X LEN=%u CRC=%02X", frame->header, frame->len, frame->crc);
                    break;

                case PARSER_WAIT:
                    goto next_input_byte;

                case PARSER_RESYNC:
                    printf("[RESYNC] Dropped invalid byte\n");
                    logger_write(LOG_WARN, "Resync: dropped invalid byte");
                    break;

                case PARSER_CRC_ERROR:
                    printf("[ERROR] CRC mismatch\n");
                    logger_write(LOG_ERROR, "CRC mismatch");
                    break;

                case PARSER_LEN_ERROR:
                    printf("[ERROR] Invalid length\n");
                    logger_write(LOG_ERROR, "Invalid length");
                    break;

                case PARSER_BUFFER_ERROR:
                    logger_write(LOG_ERROR, "Buffer operation failed inside parser");
                    fclose(fp);
                    return -1;

                case PARSER_ARG_ERROR:
                    logger_write(LOG_ERROR, "Parser received invalid argument");
                    fclose(fp);
                    return -1;

                default:
                    logger_write(LOG_ERROR, "Unknown parser status: %d", ret);
                    fclose(fp);
                    return -1;
            }
        }

next_input_byte:
        ;
    }

    logger_write(LOG_INFO, "Finished processing file: %s", path);
    fclose(fp);
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