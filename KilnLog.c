#include "KilnLog.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char* COLOR_NOR = "\x1B[0m";
static const char* COLOR_CRI = "\x1B[31m";
static const char* COLOR_ERR = "\x1B[91m";
static const char* COLOR_INF = "\x1B[37m";
static const char* COLOR_WAR = "\x1B[33m";
static const char* COLOR_DEB = "\x1B[94m";
static const char* COLOR_TRA = "\x1B[95m";

static const char* COLOR_RED_ON_YELLOW = "\x1B[93;41m";

// Settings
static int logLevel            = KLOG_DEB;
static char* logFilePath       = "kilnlog.log";
static bool silent             = false;
static bool lineWrap           = true;

void put(int level, char* msg, ...) {
    if (level > logLevel) { return; }
    
    va_list args;

    // color + level length
    const int prefixlen = 10;

    // container for the message format
    char* prefix = (char*)malloc(prefixlen + strlen(msg));
    char* fmst;

    switch(level) {
        case KLOG_CRI:
        sprintf(prefix, "%sCRI%s:%s ", COLOR_RED_ON_YELLOW, COLOR_NOR, COLOR_CRI); break;

        case KLOG_ERR:
        sprintf(prefix, "%sERR: ", COLOR_ERR); break;

        case KLOG_INF:
        sprintf(prefix, "%sINF: ", COLOR_INF); break;

        case KLOG_WAR:
        sprintf(prefix, "%sWAR: ", COLOR_WAR); break;

        case KLOG_DEB:
        sprintf(prefix, "%sDEB: ", COLOR_DEB); break;
    }

    printf("%s", prefix);
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
    printf("%c", '\n');
}

void setLevel(int level) {
    // TODO: Use 'print' once implemented
    if (level >= -1 && level <= KLOG_DEB) {
        logLevel = level;
        // print(KLOG_INFO, )
        printf("Kiln Logging Level: %d\n", level);
    } else {
        logLevel = KLOG_DEB;
        printf("Kiln Logging Level not supported: %d. Using default (%d).\n", level, logLevel);
    }
}

kiln_log_interface const KLog = { 
    put,
    setLevel
};