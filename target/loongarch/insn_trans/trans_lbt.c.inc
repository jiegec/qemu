/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (c) 2023 Jiajie Chen
 */

#ifndef CONFIG_USER_ONLY

static bool check_lbt(DisasContext *ctx)
{
    if ((ctx->base.tb->flags & HW_FLAGS_EUEN_BTE) == 0) {
        generate_exception(ctx, EXCCODE_BTD);
        return false;
    }

    return true;
}

#else

static bool check_lbt(DisasContext *ctx)
{
    return true;
}

#endif

static bool trans_movgr2scr(DisasContext *ctx, arg_movgr2scr *a)
{
    TCGv src = gpr_src(ctx, a->rj, EXT_NONE);

    if (!check_lbt(ctx)) {
        return true;
    }

    tcg_gen_st_tl(src, tcg_env,
                    offsetof(CPULoongArchState, scr[a->scrd]));

    return true;
}

static bool trans_movscr2gr(DisasContext *ctx, arg_movscr2gr *a)
{
    TCGv dst = gpr_dst(ctx, a->rd, EXT_NONE);

    if (!check_lbt(ctx)) {
        return true;
    }

    tcg_gen_ld_tl(dst, tcg_env,
                    offsetof(CPULoongArchState, scr[a->scrj]));

    return true;
}

static bool trans_x86mttop(DisasContext *ctx, arg_x86mttop *a)
{
    TCGv_i32 src = tcg_constant_i32(a->imm);

    if (!check_lbt(ctx)) {
        return true;
    }

    tcg_gen_st_i32(src, tcg_env,
                   offsetof(CPULoongArchState, ftop));

    return true;
}

static bool trans_x86mftop(DisasContext *ctx, arg_x86mftop *a)
{
    TCGv dst = gpr_dst(ctx, a->rd, EXT_NONE);

    if (!check_lbt(ctx)) {
        return true;
    }

    tcg_gen_ld32u_i64(dst, tcg_env,
                      offsetof(CPULoongArchState, ftop));

    return true;
}