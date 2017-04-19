#include "yc_ctx.h"

#include <stdlib.h>
#include <string.h>



enum {
    RBX_RE = 0,
    RDX_RE,
    RBP_RE,
    RSP_RE,
    RSI_RE,
    RDI_RE,
    IP,
    R8_RE,
    R9_RE,
    R10_RE,
    R11_RE,
    R12_RE,
    R13_RE,
    R14_RE,
    R15_RE,
};

void yc_ctx_init(yc_ctx_t *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
}

void yc_ctx_make(yc_ctx_t *ctx, char *sp, void *func, void *param)
{
    ctx->regs[RSP_RE] = sp;
    ctx->regs[IP] = func;
    ctx->regs[RDI_RE] = param;
}

void yc_ctx_swap(yc_ctx_t *old_ctx, yc_ctx_t *new_ctx) {

    __asm__ volatile (

            "popq %%rbp;"
            "leaq 8(%%rsp), %%rax;"
            "leaq 120(%%rdi), %%rsp;"
            "pushq %%r15;"
            "pushq %%r14;"
            "pushq %%r13;"
            "pushq %%r12;"
            "pushq %%r11;"
            "pushq %%r10;"
            "pushq %%r9;"
            "pushq %%r8;"
            "pushq -8(%%rax);"
            "pushq %%rdi;"
            "pushq %%rsi;"
            "pushq %%rax;" //rsp
            "pushq %%rbp;"
            "pushq %%rdx;"
            "pushq %%rbx;"

            "movq %%rsi, %%rsp;"
            "pop %%rbx;"
            "pop %%rdx;"
            "pop %%rbp;"
            "pop %%rcx;"   //rsp
            "pop %%rsi;"
            "pop %%rdi;"
            "pop %%rax;"
            "pop %%r8;"
            "pop %%r9;"
            "pop %%r10;"
            "pop %%r11;"
            "pop %%r12;"
            "pop %%r13;"
            "pop %%r14;"
            "pop %%r15;"
            "movq %%rcx, %%rsp;"
            "pushq %%rax;"
            "ret;"
            :::"rax", "rcx"

    );
}
