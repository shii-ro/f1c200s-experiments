/*
 * sys-dram.c
 *
 * Copyright(c) 2007-2022 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

// I did not found any documentation on the f1c200s DRAM / System Registers (0x01C0 0000 -- 0x01C0 1FFF)

#ifndef DRAM_H_
#define DRAM_H_

#include <stdint.h>
#include "f1c200s.h"
#include "gpio.h"
#include "ccu.h"

typedef struct {
    volatile uint32_t SCONR;        // 0x00
    volatile uint32_t STMG0R;       // 0x04
    volatile uint32_t STMG1R;       // 0x08
    volatile uint32_t SCTLR;        // 0x0c
    volatile uint32_t SREFR;        // 0x10
    volatile uint32_t SEXTMR;       // 0x14
    volatile uint32_t _reserved1[3]; // 0x18 - 0x20 (padding to skip to 0x24)
    volatile uint32_t DDLYR;        // 0x24
    volatile uint32_t DADRR;        // 0x28
    volatile uint32_t DVALR;        // 0x2c
    volatile uint32_t DRPTR0;       // 0x30
    volatile uint32_t DRPTR1;       // 0x34
    volatile uint32_t DRPTR2;       // 0x38
    volatile uint32_t DRPTR3;       // 0x3c
    volatile uint32_t SEFR;         // 0x40
    volatile uint32_t MAE;          // 0x44
    volatile uint32_t ASPR;         // 0x48
    volatile uint32_t SDLY0;        // 0x4c
    volatile uint32_t SDLY1;        // 0x50
    volatile uint32_t SDLY2;        // 0x54
    volatile uint32_t _reserved2[0x27]; // 0x58 - 0xfc (padding to skip to 0x100)
    volatile uint32_t MCR0;         // 0x100
    volatile uint32_t MCR1;         // 0x104
    volatile uint32_t MCR2;         // 0x108
    volatile uint32_t MCR3;         // 0x10c
    volatile uint32_t MCR4;         // 0x110
    volatile uint32_t MCR5;         // 0x114
    volatile uint32_t MCR6;         // 0x118
    volatile uint32_t MCR7;         // 0x11c
    volatile uint32_t MCR8;         // 0x120
    volatile uint32_t MCR9;         // 0x124
    volatile uint32_t MCR10;        // 0x128
    volatile uint32_t MCR11;        // 0x12c
    volatile uint32_t _reserved3[4]; // 0x130 - 0x13c (padding to skip to 0x140)
    volatile uint32_t BWCR;         // 0x140
} DRAM_TypeDef;

#define DRAM ((DRAM_TypeDef *) F1C200S_DRAM_BASE)

#define DRAM_BASE_ADDRESS   0x80000000
#define DRAM_MEM ((uint32_t *) DRAM_BASE_ADDRESS )

#define PLL_DDR_CLK			(156000000)
#define SDR_T_CAS			(0x2U)
#define SDR_T_RAS			(0x8U)
#define SDR_T_RCD			(0x3U)
#define SDR_T_RP			(0x3U)
#define SDR_T_WR			(0x3U)
#define SDR_T_RFC			(0xdU)
#define SDR_T_XSR			(0xf9U)
#define SDR_T_RC			(0xbU)
#define SDR_T_INIT			(0x8U)
#define SDR_T_INIT_REF		(0x7U)
#define SDR_T_WTR			(0x2U)
#define SDR_T_RRD			(0x2U)
#define SDR_T_XP			(0x0U)

enum dram_type_t
{
	DRAM_TYPE_SDR	= 0,
	DRAM_TYPE_DDR	= 1,
	DRAM_TYPE_MDDR	= 2,
};

struct dram_para_t
{
  uint32_t base;                 // dram base address
  uint32_t size;                 // dram size        (unit: MByte)
  uint32_t clk;                  // dram work clock  (unit: MHz)
  uint32_t access_mode;          // 0: interleave mode 1: sequence mode
  uint32_t cs_num;               // dram chip count  1: one chip  2: two chip
  uint32_t ddr8_remap;           // for 8bits data width DDR 0: normal  1: 8bits
  enum dram_type_t sdr_ddr; // ddr/ddr2/sdr/mddr/lpddr/...
  uint32_t bwidth;               // dram bus width
  uint32_t col_width;            // column address width
  uint32_t row_width;            // row address width
  uint32_t bank_size;            // dram bank count
  uint32_t cas;                  // dram cas
};

void DRAM_Init(void);

#endif