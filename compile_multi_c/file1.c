#include "stdio.h"
#include "file2.h"

int main(void){
    printf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
    foo();
    return 0;
}
