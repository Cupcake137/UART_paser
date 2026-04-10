#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "logger.h"

static FILE *g_log_fp = NULL;

static const char *level_to_string(LogLevel level)
{
    switch (level) {
        case LOG_INFO:  return "INFO";
        case LOG_WARN:  return "WARN";
        case LOG_ERROR: return "ERROR";
        default:        return "UNKNOWN";
    }
}

int logger_init(const char *path)
{
    if (path == NULL) {
        return -1;
    }

    g_log_fp = fopen(path, "w");
    if (g_log_fp == NULL) {
        return -1;
    }

    return 0;
}

void logger_write(LogLevel level, const char *fmt, ...)
{
    if (g_log_fp == NULL || fmt == NULL) {
        return;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    if (tm_info == NULL) {
        return;
    }

    char time_buf[32];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(g_log_fp, "[%s] [%s] ", time_buf, level_to_string(level));

    va_list args;
    va_start(args, fmt);
    vfprintf(g_log_fp, fmt, args);
    va_end(args);

    fprintf(g_log_fp, "\n");
    fflush(g_log_fp);
}

void logger_close(void)
{
    if (g_log_fp != NULL) {
        fclose(g_log_fp);
        g_log_fp = NULL;
    }
}