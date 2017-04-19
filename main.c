#include "yc_coroutine.h"

#include <stdio.h>
#include <stdint.h>


void func(void *data)
{
    int64_t num = (int64_t)data;
    for (int i = 0; i < num; ++i) {
        printf("%d\n", i);
        yc_yield();
    }
}


int main()
{
    yc_init();
    yc_coroutine_t *co = yc_create(func, (void *)10);
    yc_coroutine_t *co1 = yc_create(func, (void *)10);

    int i = 0;
    while (i < 11) {
        ++i;
        yc_resume(co);
        yc_resume(co1);
    }

    yc_destory(co);
    yc_destory(co1);

    return 0;
}
