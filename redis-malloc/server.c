#include "stdio.h"
#include "atomicvar.h"
#include "zmalloc.h"
int main(int argc, char **argv){
    redisAtomic long  long i = 10;
    atomicIncr(i, 3);
    printf("hello %lld\n",i);
    char *p;
    p = zmalloc(10);
    p = "hello";
    printf("hello %s\n",p);
    int accurate;
    accurate = 10;
#ifdef REDIS_TEST
    zmalloc_test( argc,argv,accurate );
#endif
    return 0;
}
