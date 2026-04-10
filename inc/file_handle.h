#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

#include <stdint.h>
#include "buffer.h"
#include "byte_processing.h"

int process_test_file(const char *path, CircularBuffer *cb, Frame *frame);

#endif //FILE_HANDLE_H