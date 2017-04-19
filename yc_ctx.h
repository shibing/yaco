
#pragma once

#include <stddef.h>

typedef struct {
    void *regs[15];
} yc_ctx_t;


void yc_ctx_init(yc_ctx_t *);

void yc_ctx_make(yc_ctx_t *, char *sp, void *func, void *param);

void yc_ctx_swap(yc_ctx_t * , yc_ctx_t *);
