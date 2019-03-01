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
    if (level < KLOG_CRI) {
        put(KLOG_WAR, "Log level too low (%d). Using %d instead.", level, KLOG_INF);
        level = KLOG_INF; 
    }
    
    va_list args;

    // max length of the final formatted message.
    // 512 bytes for va and 50 to prevent overflow 
    const size_t maxLen = strlen(msg) + 50 + 512;

    // the final formatted message
    char* fmsg = (char*)malloc(maxLen);

    switch(level) {
        case KLOG_CRI:
        sprintf(fmsg, "%sCRI%s%s: ", COLOR_RED_ON_YELLOW, COLOR_NOR, COLOR_CRI); break;

        case KLOG_ERR:
        sprintf(fmsg, "%sERR: ", COLOR_ERR); break;

        case KLOG_INF:
        sprintf(fmsg, "%sINF: ", COLOR_INF); break;

        case KLOG_WAR:
        sprintf(fmsg, "%sWAR: ", COLOR_WAR); break;

        case KLOG_DEB:
        sprintf(fmsg, "%sDEB: ", COLOR_DEB); break;
    }

    va_start(args, msg);
    vsprintf(fmsg + strlen(fmsg), msg, args);
    va_end(args);
    sprintf(fmsg + strlen(fmsg), "\n");

    if (strlen(fmsg) > maxLen) {
        int difference = strlen(fmsg) - maxLen + 1;
        put(KLOG_ERR, "Log exceeded max buffer size. Truncated %d bytes.", difference);
        sprintf(fmsg + maxLen - 1, "\n");
    }

    if (!silent) {
        printf("%s%s", fmsg, COLOR_NOR);
        fflush(stdout);
    }

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