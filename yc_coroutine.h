#pragma once

#include "yc_ctx.h"

yc_ctx_t m;


typedef void (* yc_co_func_t)(void *);

typedef struct yc_coroutine_s yc_coroutine_t;

enum {
    CO_NUM = 128
};

struct yc_coroutine_s  {
    yc_ctx_t ctx;
    char *sp;
    char *bp;
    int stack_size;
    int state;
    yc_co_func_t func;
    void *param;
} ;

void yc_init();
yc_coroutine_t * yc_create(yc_co_func_t, void *param);
void yc_resume(yc_coroutine_t *);
void yc_yield();
void yc_destory(yc_coroutine_t *);
