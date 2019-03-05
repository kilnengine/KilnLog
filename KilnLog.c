#include "KilnLog.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

char* getTimeStr();

/**
 * Write output to std out/err and to the log file.
 * @param int level
 * @param char* msg Formatted message string.
 * @param ... Arguments to be used with the format string.
 */

void put(int level, const char* msg, ...) {
    if (level > logLevel) { return; }
    if (level < KLOG_CRI) {
        put(KLOG_WAR, "Log level too low (%d). Using %d instead.", level, KLOG_INF);
        level = KLOG_INF; 
    }
    
    va_list args;

    // max length of the final formatted message.
    // 512 bytes for va and 50 to prevent overflow 
    const size_t maxLen = strlen(msg) + 50 + 512;

    // the color of the message based on the log level
    char* color = (char*)malloc(10);

    // the final formatted message
    char* fmsg = (char*)malloc(maxLen);

    // set color and prefix
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

    // add date string to message
    char* timestr = getTimeStr();
    sprintf(fmsg + strlen(fmsg), "[%s] ", timestr);

    // format the message with the variable args
    // and append to the log level prefix
    va_start(args, msg);
    vsprintf(fmsg + strlen(fmsg), msg, args);
    va_end(args);
    sprintf(fmsg + strlen(fmsg), "\n");

    // verify that everything fits into the allocated buffer
    // if not, truncate. the final char should be a \n
    if (strlen(fmsg) > maxLen) {
        int difference = strlen(fmsg) - maxLen + 1;
        put(KLOG_ERR, "Log exceeded max buffer size. Truncated %d bytes.", difference);
        sprintf(fmsg + maxLen - 1, "%s\n", COLOR_NOR);
    }

    // if not silent, output to stdout or stderr with the ansi color code
    if (!silent) {
        FILE* outTo;
        if (level < KLOG_INF) {
            outTo = stderr;
        } else {
            outTo = stdout;
        }
        fprintf(outTo, "%s%s%s", color, fmsg, COLOR_NOR);
        fflush(outTo);
    }

    // append to the log file
    FILE* file = fopen(logFile, "a");
    fprintf(file, fmsg);
    fflush(file);
    fclose(file);

    free(color);
    free(timestr);
    free(fmsg);
}

/**
 * Sets the highest level log that should be used.
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

/**
 * Set the file to write logs to.
 * @param file The new log file
 */

void setFile(const char* file) {
    memset(logFile, 0, 256);
    strcpy(logFile, file);
    put(KLOG_INF, "Writing logs to file '%s'.", file);
}

/**
 * Disable or enable silent logging. Silent does not output to stdout or stderr.
 * @param bool _silent True to enable silent logging.
 */

void setSilent(const bool _silent) {
    silent = _silent;
    put(KLOG_INF, "Silent logging is %s.", silent ? "active" : "inactive");
}

/**
 * Clears the log file.
 */

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

char* getTimeStr() {
    time_t t = time(NULL);
    struct tm* ltime = localtime(&t);

    char* result = (char*)malloc(25);

    strftime(result, 25, "%F|%T", ltime);

    return result;
}