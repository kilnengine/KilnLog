#include "KilnLog.h"
#include "stdio.h"

int main(int argc, const char* argv[]) {
    klog.setLevel(KILN_LOG_DEBUG);
    klog.print(KILN_LOG_CRITICAL, "TEST");
    klog.print(KILN_LOG_ERROR, "TEST");
    klog.print(KILN_LOG_INFO, "TEST");
    klog.print(KILN_LOG_WARN, "TEST");
    klog.print(KILN_LOG_DEBUG, "TEST");
    return 0;
}