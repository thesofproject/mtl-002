/*
 * Copyright (c) 2019 Intel Corporation
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __INC_MEMORY_H
#define __INC_MEMORY_H

#include <autoconf.h>

/* L2 HP SRAM */
#define HP_RAM_RESERVE_HEADER_SPACE		0x00010000

#ifdef CONFIG_BOOTLOADER_MCUBOOT
#define SRAM_BASE (DT_L2_SRAM_BASE + CONFIG_BOOTLOADER_SRAM_SIZE * 1K)
#define SRAM_SIZE (DT_L2_SRAM_SIZE - CONFIG_BOOTLOADER_SRAM_SIZE * 1K)
#else
#define SRAM_BASE (DT_L2_SRAM_BASE)
#define SRAM_SIZE (DT_L2_SRAM_SIZE)
#endif

/* The reset vector address in SRAM and its size */
#define XCHAL_RESET_VECTOR0_PADDR_SRAM		SRAM_BASE
#define MEM_RESET_TEXT_SIZE			0x268
#define MEM_RESET_LIT_SIZE			0x8

/* This is the base address of all the vectors defined in SRAM */
#define XCHAL_VECBASE_RESET_PADDR_SRAM \
	(SRAM_BASE + HP_RAM_RESERVE_HEADER_SPACE)

#define MEM_VECBASE_LIT_SIZE			0x178

/* The addresses of the vectors in SRAM.
 * Only the memerror vector continues to point to its ROM address.
 */
#define XCHAL_INTLEVEL2_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x180)

#define XCHAL_INTLEVEL3_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x1C0)

#define XCHAL_INTLEVEL4_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x200)

#define XCHAL_INTLEVEL5_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x240)

#define XCHAL_INTLEVEL6_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x280)

#define XCHAL_INTLEVEL7_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x2C0)

#define XCHAL_KERNEL_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x300)

#define XCHAL_USER_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x340)

#define XCHAL_DOUBLEEXC_VECTOR_PADDR_SRAM \
	(XCHAL_VECBASE_RESET_PADDR_SRAM + 0x3C0)

#define VECTOR_TBL_SIZE				0x0400

/* Vector and literal sizes */
#define MEM_VECT_LIT_SIZE			0x8
#define MEM_VECT_TEXT_SIZE			0x38
#define MEM_VECT_SIZE				(MEM_VECT_TEXT_SIZE +\
						MEM_VECT_LIT_SIZE)

/* The memerror vector address is copied as is from core-isa.h */
#define XCHAL_MEMERROR_VECTOR_PADDR		0xBEFE0400

#define MEM_ERROR_TEXT_SIZE			0x180
#define MEM_ERROR_LIT_SIZE			0x8

/* text and data share the same L2 HP SRAM.
 * So, they lie next to each other.
 */
#define RAM_BASE \
	(SRAM_BASE + HP_RAM_RESERVE_HEADER_SPACE + VECTOR_TBL_SIZE)

#define RAM_SIZE \
	(SRAM_SIZE - HP_RAM_RESERVE_HEADER_SPACE - VECTOR_TBL_SIZE)

/* Location for the intList section which is later used to construct the
 * Interrupt Descriptor Table (IDT). This is a bogus address as this
 * section will be stripped off in the final image.
 */
#define IDT_BASE				(RAM_BASE + RAM_SIZE)

/* size of the Interrupt Descriptor Table (IDT) */
#define IDT_SIZE				0x2000

/* low power ram where DMA buffers are typically placed */
#define LPRAM_BASE				(DT_LP_SRAM_BASE)
#define LPRAM_SIZE				(DT_LP_SRAM_SIZE)

#define HEAP_HP_BUFFER_BASE	SRAM_BASE
#define HEAP_HP_BUFFER_SIZE	0x8000
#define SRAM_WND_BASE		(HEAP_HP_BUFFER_BASE + HEAP_HP_BUFFER_SIZE)
#define SRAM_SW_REG_BASE	(SRAM_INBOX_BASE + SRAM_INBOX_SIZE)
#define SRAM_SW_REG_SIZE	0x1000
#define MAILBOX_SW_REG_BASE	SRAM_SW_REG_BASE
#define MAILBOX_SW_REG_SIZE	SRAM_SW_REG_SIZE

#define SRAM_TRACE_BASE		SRAM_WND_BASE
#define SRAM_TRACE_SIZE		0x2000
#define SRAM_DEBUG_BASE		(SRAM_TRACE_BASE + SRAM_TRACE_SIZE)
#define SRAM_DEBUG_SIZE		0x800
#define SRAM_EXCEPT_BASE	(SRAM_DEBUG_BASE + SRAM_DEBUG_SIZE)
#define SRAM_EXCEPT_SIZE	0x800
#define SRAM_STREAM_BASE	(SRAM_EXCEPT_BASE + SRAM_EXCEPT_SIZE)
#define SRAM_STREAM_SIZE	0x1000
#define SRAM_INBOX_BASE		(SRAM_STREAM_BASE + SRAM_STREAM_SIZE)
#define SRAM_INBOX_SIZE		0x2000
#define SRAM_OUTBOX_BASE	(SRAM_SW_REG_BASE + SRAM_SW_REG_SIZE)
#define SRAM_OUTBOX_SIZE	0x1000

/* Mailbox */
#define MAILBOX_HOSTBOX_SIZE	SRAM_INBOX_SIZE
#define MAILBOX_HOSTBOX_BASE	SRAM_INBOX_BASE

#define MAILBOX_DSPBOX_SIZE	SRAM_OUTBOX_SIZE
#define MAILBOX_DSPBOX_BASE	SRAM_OUTBOX_BASE

#define MAILBOX_TRACE_SIZE	SRAM_TRACE_SIZE
#define MAILBOX_TRACE_BASE	SRAM_TRACE_BASE

#define MAILBOX_DEBUG_SIZE	SRAM_DEBUG_SIZE
#define MAILBOX_DEBUG_BASE	SRAM_DEBUG_BASE

#define MAILBOX_EXCEPTION_SIZE	SRAM_EXCEPT_SIZE
#define MAILBOX_EXCEPTION_BASE	SRAM_EXCEPT_BASE
#define MAILBOX_EXCEPTION_OFFSET SRAM_DEBUG_SIZE

#define MAILBOX_STREAM_SIZE	SRAM_STREAM_SIZE
#define MAILBOX_STREAM_BASE	SRAM_STREAM_BASE
#define MAILBOX_STREAM_OFFSET	(SRAM_DEBUG_SIZE + SRAM_EXCEPT_SIZE)

/* IPC MMIO and registers */
#define IPC_HOST_BASE		0x00001180
#define IPC_DIPCIE		0x0C
#define IPC_DIPCI		0x08

/* SHIM MMIO */
#define SHIM_BASE		0x00001000

#endif /* __INC_MEMORY_H */
