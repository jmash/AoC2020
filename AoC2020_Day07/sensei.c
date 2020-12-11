#include <stdio.h>
#include <stdlib.h>

int main()
{
    typedef struct {
        int a[100];
        char b;
        double * c;
    } mystruct_t;
    mystruct_t d[10];
    mystruct_t * ap = d;
    printf("%x %u\n",ap, ap); 
    printf("%x %u\n", ap+1, ap+1);
    printf("%x %u\n", &d[10]-d, &d[10]-d);
    return 0;
}
