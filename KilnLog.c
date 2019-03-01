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
static int logLevel          = KLOG_DEB;
static char* logFilePath     = "kilnlog.log";
static bool silent           = false;
static bool lineWrap         = true;

/**
 * Write output to std out/err and to the log file.
 * @param int level
 * @param char* msg Formatted message string.
 * @param ... Arguments to be used with the format string.
 */

void put(int level, char* msg, ...) {
    if (level > logLevel) { return; }
    
    va_list args;

    // color + level length
    const int prefixlen = 10;

    // container for the message format
    char* prefix = (char*)malloc(prefixlen);
    char* fmsg = (char*)malloc(strlen(prefix) + strlen(msg) + 512);

    switch(level) {
        case KLOG_CRI:
        sprintf(prefix, "%sCRI%s%s: ", COLOR_RED_ON_YELLOW, COLOR_NOR, COLOR_CRI); break;

        case KLOG_ERR:
        sprintf(prefix, "%sERR: ", COLOR_ERR); break;

        case KLOG_INF:
        sprintf(prefix, "%sINF: ", COLOR_INF); break;

        case KLOG_WAR:
        sprintf(prefix, "%sWAR: ", COLOR_WAR); break;

        case KLOG_DEB:
        sprintf(prefix, "%sDEB: ", COLOR_DEB); break;
    }

    sprintf(fmsg, "%s%s\n", prefix, msg);
    va_start(args, msg);
    vsprintf(fmsg, fmsg, args);
    va_end(args);

    if (!silent) {
        printf("%s", fmsg);
    }

    free(prefix);
    free(fmsg);
}

/**
 * Sets what the highest level log that should be used.
 * @param int level
 */

void setLevel(int level) {
    if (level >= KLOG_ERR && level <= KLOG_DEB) {
        logLevel = level;
        put(KLOG_INF, "Logging level has been set to %d.", level);
    } else {
        int defaultLevel = KLOG_DEB;
        put(KLOG_WAR, "Attempted to use unsupported log level (%d). Using default (%d).", level, defaultLevel);
        setLevel(defaultLevel);
    }
}



kiln_log_interface const KLog = { 
    put,
    setLevel
};