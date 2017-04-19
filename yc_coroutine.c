#include "yc_coroutine.h"

#include <stdlib.h>
#include <assert.h>


static yc_coroutine_t main_routine;

static yc_coroutine_t *pre_routine = 0;
static yc_coroutine_t *cur_routine = 0;

enum {
    STACK_SIZE = 8 * 1024
};

enum state {
    READY,
    RUNNING,
    END
};

static void coroutine(yc_coroutine_t *co)
{
    co->func(co->param);
    co->state = END;
    yc_yield();
}

void yc_init()
{
    yc_ctx_init(&main_routine.ctx);
    cur_routine = &main_routine;
}

yc_coroutine_t *yc_create(yc_co_func_t func, void *param)
{
    yc_coroutine_t *co = malloc(sizeof *co);

    co->sp = malloc(STACK_SIZE);
    co->stack_size = STACK_SIZE;
    co->bp = co->sp + co->stack_size;

    co->state =  READY;
    co->func = func;
    co->param = param;

    yc_ctx_init(&co->ctx);

    return co;

}

void yc_resume(yc_coroutine_t *co)
{
    if (co->state == READY) {
        yc_ctx_make(&co->ctx, co->bp, coroutine, co);
        co->state = RUNNING;
    }
    pre_routine = cur_routine;
    cur_routine = co;
    yc_ctx_swap(&pre_routine->ctx , &cur_routine->ctx);
}

void yc_yield() 
{
    yc_coroutine_t *tmp = cur_routine;
    cur_routine = pre_routine;
    pre_routine = tmp;
    yc_ctx_swap(&pre_routine->ctx, &cur_routine->ctx);
}

void yc_destory(yc_coroutine_t *co)
{
    free(co->sp);
    free(co);
}
