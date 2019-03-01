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
static char logFile[256]     = "kilnlog.log";
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

    char* color = (char*)malloc(10);

    // the final formatted message
    char* fmsg = (char*)malloc(maxLen);

    switch(level) {
        case KLOG_CRI:
        sprintf(color, COLOR_CRI);
        sprintf(fmsg, "CRI: ");
        break;

        case KLOG_ERR:
        sprintf(color, COLOR_ERR);
        sprintf(fmsg, "ERR: ");
        break;

        case KLOG_INF:
        sprintf(color, COLOR_INF);
        sprintf(fmsg, "INF: ");
        break;

        case KLOG_WAR:
        sprintf(color, COLOR_WAR);
        sprintf(fmsg, "WAR: ");
        break;

        case KLOG_DEB:
        sprintf(color, COLOR_DEB);
        sprintf(fmsg, "DEB: ");
        break;
    }

    va_start(args, msg);
    vsprintf(fmsg + strlen(fmsg), msg, args);
    va_end(args);
    sprintf(fmsg + strlen(fmsg), "\n");

    if (strlen(fmsg) > maxLen) {
        int difference = strlen(fmsg) - maxLen + 1;
        put(KLOG_ERR, "Log exceeded max buffer size. Truncated %d bytes.", difference);
        sprintf(fmsg + maxLen - 1, "%s\n", COLOR_NOR);
    }

    if (!silent) {
        printf("%s%s%s", color, fmsg, COLOR_NOR);
        fflush(stdout);
    }

    FILE* file = fopen(logFile, "a");
    fprintf(file, fmsg);
    fflush(file);
    fclose(file);

    free(color);
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

void setFile(const char* file) {
    memset(logFile, 0, 256);
    strcpy(logFile, file);
    put(KLOG_INF, "Writing logs to file '%s'.", file);
}

void setSilent(const bool _silent) {
    silent = _silent;
    put(KLOG_INF, "Silent logging is %s.", silent ? "active" : "inactive");
}

void flush() {
    FILE* file;
    if (file = fopen(logFile, "w")) {
        put(KLOG_INF, "Log file flushed.");
    } else {
        put(KLOG_ERR, "Log file was not accessible when attempting to flush! (%s)", logFile);
    }
}


kiln_log_interface const KLog = { 
    put,
    setLevel,
    setFile,
    setSilent,
    flush
};