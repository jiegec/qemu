/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * LoongArch CPU parameters for QEMU.
 *
 * Copyright (c) 2021 Loongson Technology Corporation Limited
 */

#ifndef LOONGARCH_CPU_PARAM_H
#define LOONGARCH_CPU_PARAM_H

#ifdef TARGET_LOONGARCH32
#define TARGET_LONG_BITS 32
#define TARGET_PHYS_ADDR_SPACE_BITS 36
#define TARGET_VIRT_ADDR_SPACE_BITS 32
#else
#define TARGET_LONG_BITS 64
#define TARGET_PHYS_ADDR_SPACE_BITS 48
#define TARGET_VIRT_ADDR_SPACE_BITS 48
#endif

#define TARGET_PAGE_BITS 14

#endif
