#include <stdio.h>
#include "file2.h"

void foo(void) {
    printf("%s:%s:%d \n", __FILE__, __FUNCTION__, __LINE__);
    return;
}

