#include "KilnLog.h"
#include "stdio.h"

int main(int argc, const char* argv[]) {
    KLog.put(KLOG_CRI, "TEST");
    KLog.put(KLOG_ERR, "TEST");
    KLog.put(KLOG_INF, "TEST");
    KLog.put(KLOG_WAR, "TEST");
    KLog.put(KLOG_DEB, "TEST");
    KLog.put(KLOG_CRI - 1, "Low Level");

    printf("TESTESTEST\n");

    return 0;
}