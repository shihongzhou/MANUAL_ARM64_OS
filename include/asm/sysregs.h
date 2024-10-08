
#ifndef ___SYS_REGS__H
#define ___SYS_REGS__H

#define HCR_RW          (1 << 31)

/* 无虚拟化主机扩展，设置el1运行在AArch64下*/
#define HCR_HOST_NVHE_FLAGS (HCR_RW)
/* 设置为小端模式*/
#define SCTLR_EE_LITTLE_ENDIAN          (0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN         (0 << 24)
/* 关闭MMU */
#define SCTLR_MMU_DISABLED   (0 << 0)
#define SCTLR_VALUE_MMU_DISABLED (SCTLR_MMU_DISABLED | SCTLR_EE_LITTLE_ENDIAN | SCTLR_EOE_LITTLE_ENDIAN )

#define SPSR_MASK_ALL (7 << 6)
#define SPSR_EL1h (5 << 0)
#define SPSR_EL2h (9 << 0)
#define SPSR_EL1 (SPSR_MASK_ALL | SPSR_EL1h)
#define SPSR_EL2 (SPSR_MASK_ALL | SPSR_EL2h)

#define CurrentEL_EL1 (1 << 2)
#define CurrentEL_EL2 (2 << 2)
#define CurrentEL_EL3 (3 << 2)


#endif
