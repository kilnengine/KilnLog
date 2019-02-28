#include "KilnLog.h"
#include <stdarg.h>
#include <stdio.h>

static const char* COLOR_NORM  = "\x1B[0m";
static const char* COLOR_CRIT  = "\x1B[31m";
static const char* COLOR_ERR   = "\x1B[91m";
static const char* COLOR_INFO  = "\x1B[37m";
static const char* COLOR_WARN  = "\x1B[33m";
static const char* COLOR_DEBUG = "\x1B[94m";
static const char* COLOR_VERB  = "\x1B[36m";
static const char* COLOR_LOG   = "\x1B[90m";
static const char* COLOR_TRACE = "\x1B[95m";

static int verbosity           = KILN_LOG_DEBUG;
static char* logFile           = "kiln.log";
static bool isSilent           = false;
static bool lineWrap           = true;

void print(int verbosity, char* msg, ...) {
    va_list arg;

    printf(msg);
}

kiln_log_interface const klog = { 
    print
};