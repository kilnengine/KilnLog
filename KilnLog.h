#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Level definitions
#define KLOG_CRI -2
#define KLOG_ERR -1
#define KLOG_INF 0
#define KLOG_WAR 1
#define KLOG_DEB 2

// Interface
typedef struct {
    void (*const put)(int level, char* msg, ...);
    // void (*const trace)(void);
    void (*const setLevel)(int level);
    // void (*const setFileLocation)(const char* file);
    // void (*const setSilent)(bool silent);
    // void (*const setLineWrap)(bool wrap);
    // void (*const flush)(void);
    // void (*const loadConfig)(const char* config);
} kiln_log_interface;

extern kiln_log_interface const KLog;

#ifdef __cplusplus
}
#endif