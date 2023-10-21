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
