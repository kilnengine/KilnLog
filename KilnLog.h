#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Verbosity definitions
#define KILN_LOG_CRITICAL   -2
#define KILN_LOG_ERROR      -1
#define KILN_LOG_INFO       0
#define KILN_LOG_WARN       1
#define KILN_LOG_DEBUG      2

// Interface
typedef struct {
    void (*const print)(int verbosity, char* msg, ...);
    // void (*const trace)(void);
    // void (*const setVerbosity)(int verbosity);
    // void (*const setFileLocation)(const char* file);
    // void (*const setSilent)(bool silent);
    // void (*const setLineWrap)(bool wrap);
    // void (*const flush)(void);
    // void (*const loadConfig)(const char* config);
} kiln_log_interface;

extern kiln_log_interface const klog;

#ifdef __cplusplus
}
#endif