#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

typedef enum {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

int logger_init(const char *path);
void logger_write(LogLevel level, const char *fmt, ...);
void logger_close(void);

#endif