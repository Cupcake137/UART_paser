#include <stdio.h>
#include <stdint.h>

#include "buffer.h"
#include "byte_processing.h"
#include "file_handle.h"

int main(void) {
    CircularBuffer cb;
    Frame frame;

    cb_init(&cb);

    //open test file
    process_test_file("./test/stream_test.txt", &cb, &frame);
    
    return 0;
}
