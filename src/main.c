#include <stdio.h>
#include <stdint.h>

#include "buffer.h"
#include "byte_processing.h"
#include "file_handle.h"
#include "logger.h"

int main(void) {
    CircularBuffer cb;
    Frame frame;

    cb_init(&cb);

    if (logger_init("./test/parser.log") != 0) {
        printf("Failed to open log file\n");
        return -1;
    }

    logger_write(LOG_INFO, "UART parser started");

    //open test file
    process_test_file("./test/stream_test.txt", &cb, &frame);
    
    logger_write(LOG_INFO, "UART parser finished");
    logger_close();

    return 0;
}
