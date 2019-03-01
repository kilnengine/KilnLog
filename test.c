#include "KilnLog.h"
#include "stdio.h"

int main(int argc, const char* argv[]) {
    KLog.setLevel(5);
    KLog.put(KLOG_CRI, "TEST");
    KLog.put(KLOG_ERR, "TEST");
    KLog.put(KLOG_INF, "TEST");
    KLog.put(KLOG_WAR, "TEST");
    KLog.put(KLOG_DEB, "TEST");
    return 0;
}