#include "KilnLog.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char* COLOR_NORM  = "\x1B[0m";
static const char* COLOR_CRIT  = "\x1B[31m";
static const char* COLOR_ERR   = "\x1B[91m";
static const char* COLOR_INFO  = "\x1B[37m";
static const char* COLOR_WARN  = "\x1B[33m";
static const char* COLOR_DEBUG = "\x1B[94m";
static const char* COLOR_TRACE = "\x1B[95m";

static const char* COLOR_RED_ON_YELLOW = "\x1B[93;41m";

// Settings
static int logLevel            = KILN_LOG_DEBUG;
static char* logFilePath       = "kilnlog.log";
static bool silent             = false;
static bool lineWrap           = true;

void print(int level, char* msg, ...) {
    if (level > logLevel) { return; }
    
    va_list arg;

    // color + level
    const int prefixlen = 10;

    // container for the message format
    char* fmsg = (char*)malloc(prefixlen);

    switch(level) {
        case KILN_LOG_CRITICAL:
        sprintf(fmsg, "%sCRI%s:%s ", COLOR_RED_ON_YELLOW, COLOR_NORM, COLOR_CRIT); break;

        case KILN_LOG_ERROR:
        sprintf(fmsg, "%sERR: ", COLOR_ERR); break;

        case KILN_LOG_INFO:
        sprintf(fmsg, "%sINF: ", COLOR_INFO); break;

        case KILN_LOG_WARN:
        sprintf(fmsg, "%sWAR: ", COLOR_WARN); break;

        case KILN_LOG_DEBUG:
        sprintf(fmsg, "%sDEB: ", COLOR_DEBUG); break;
    }

    printf("%s%s\n", fmsg, msg);
}

void setLevel(int level) {
    // TODO: Use 'print' once implemented
    if (level >= -1 && level <= KILN_LOG_DEBUG) {
        logLevel = level;
        // print(KILN_LOG_INFO, )
        printf("Kiln Logging Level: %d\n", level);
    } else {
        logLevel = KILN_LOG_DEBUG;
        printf("Kiln Logging Level not supported: %d. Using default (%d).\n", level, logLevel);
    }
}

kiln_log_interface const klog = { 
    print,
    setLevel
};