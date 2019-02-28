#include "KilnLog.h"
#include "stdio.h"

int main(int argc, const char* argv[]) {
    klog.print(KILN_LOG_INFO, "TEST");
    return 0;
}