#include "dram.h"
#include "uart.h"

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

static inline void sdelay(int loops)
{
    __asm__ volatile("1:\n"
                    "subs %0, %1, #1\n"
		            "bne 1b":"=r" (loops):"0"(loops));
}

static void dram_delay(int ms)
{
	sdelay(ms * 2 * 1000);
}

static int dram_initial(void)
{
	unsigned int time = 0xffffff;

    DRAM->SCTLR |= 0x1;

	while((DRAM->SCTLR & 0x1) && time--)
	{
		if(time == 0)
			return 0;
	}
	return 1;
}

static int dram_delay_scan(void)
{
    unsigned int time = 0xffffff;

    DRAM->DDLYR = DRAM->DDLYR | 0x1;

    while ((DRAM->DDLYR & 0x1) && time--)
    {
        if (time == 0)
            return 0;
    }
    return 1;
}

static void dram_set_autofresh_cycle(uint32_t clk)
{
	uint32_t val = 0;
	uint32_t row = 0;
	uint32_t temp = 0;

	row = DRAM->SCONR;
	row &= 0x1e0;
	row >>= 0x5;

	if(row == 0xc)
	{
		if(clk >= 1000000)
		{
			temp = clk + (clk >> 3) + (clk >> 4) + (clk >> 5);
			while(temp >= (10000000 >> 6))
			{
				temp -= (10000000 >> 6);
				val++;
			}
		}
		else
		{
			val = (clk * 499) >> 6;
		}
	}
	else if(row == 0xb)
	{
		if(clk >= 1000000)
		{
			temp = clk + (clk >> 3) + (clk >> 4) + (clk >> 5);
			while(temp >= (10000000 >> 7))
			{
				temp -= (10000000 >> 7);
				val++;
			}
		}
		else
		{
			val = (clk * 499) >> 5;
		}
	}

    DRAM->SREFR = val;
}

static int dram_para_setup(struct dram_para_t * para)
{
	uint32_t val = 0;

    val = (para->ddr8_remap) |
    	(0x1 << 1) |
		((para->bank_size >> 2) << 3) |
		((para->cs_num >> 1) << 4) |
		((para->row_width - 1) << 5) |
		((para->col_width - 1) << 9) |
		((para->sdr_ddr ? (para->bwidth >> 4) : (para->bwidth >> 5)) << 13) |
		(para->access_mode << 15) |
		(para->sdr_ddr << 16);

    DRAM->SCONR = val;
    DRAM->SCTLR |= (0x1 << 19);
	return dram_initial();
}

static uint32_t dram_check_delay(uint32_t bwidth)
{
	uint32_t dsize;
	uint32_t i,j;
	uint32_t num = 0;
	uint32_t dflag = 0;

	dsize = ((bwidth == 16) ? 4 : 2);
	for(i = 0; i < dsize; i++)
	{
		if(i == 0)
			dflag = DRAM->DRPTR0;
		else if(i == 1)
			dflag = DRAM->DRPTR1;
		else if(i == 2)
			dflag = DRAM->DRPTR2;
		else if(i == 3)
			dflag = DRAM->DRPTR3;

		for(j = 0; j < 32; j++)
		{
			if(dflag & 0x1)
				num++;
			dflag >>= 1;
		}
	}
	return num;
}

static int sdr_readpipe_scan(void)
{
    uint32_t k = 0;

    for (k = 0; k < 32; k++)
    {
        DRAM_MEM[4 * k] = k;
    }
    for (k = 0; k < 32; k++)
    {
        if (DRAM_MEM[4 * k] != k)
            return 0;
    }
    return 1;
}

static uint32_t sdr_readpipe_select(void)
{
    uint32_t value = 0;
    uint32_t i = 0;
    for (i = 0; i < 8; i++)
    {
        DRAM->SCTLR &= ~(0x7 << 6);
        DRAM->SCTLR |= (i << 6);

        if (sdr_readpipe_scan())
        {
            value = i;
            return value;
        }
    }
    return value;
}

static uint32_t dram_check_type(struct dram_para_t * para)
{
	uint32_t times = 0;
	uint32_t i;

	for(i = 0; i < 8; i++)
	{
		DRAM->SCTLR = ((DRAM->SCTLR & ~(0x7 << 6)) | (i << 6));
        
		dram_delay_scan();
		if(DRAM->DDLYR & 0x30)
			times++;
	}

	if(times == 8)
	{
		para->sdr_ddr = DRAM_TYPE_SDR;
		return 0;
	}
	else
	{
		para->sdr_ddr = DRAM_TYPE_DDR;
		return 1;
	}
}

static uint32_t dram_scan_readpipe(struct dram_para_t *para)
{
    uint32_t i, rp_best = 0, rp_val = 0;
    uint32_t readpipe[8];

    if (para->sdr_ddr == DRAM_TYPE_DDR)
    {
        for (i = 0; i < 8; i++)
        {
            DRAM->SCTLR = ((DRAM->SCTLR & ~(0x7 << 6)) | (i << 6));
            dram_delay_scan();
            readpipe[i] = 0;

            if ((((DRAM->DDLYR >> 4) & 0x3) == 0x0) && ((((DRAM->DDLYR >> 4) & 0x3) & 0x1) == 0x0))
            {
                readpipe[i] = dram_check_delay(para->bwidth);
            }
            if (rp_val < readpipe[i])
            {
                rp_val = readpipe[i];
                rp_best = i;
            }
        }

        DRAM->SCTLR = ((DRAM->SCTLR & ~(0x7 << 6)) | (rp_best << 6));
        dram_delay_scan();
    }
    else
    {
        DRAM->SCONR &= ~0x16000;
        rp_best = sdr_readpipe_select();
        DRAM->SCTLR = ((DRAM->SCTLR & ~(0x7 << 6)) | (rp_best << 6));
    }
    return 0;
}

static uint32_t dram_get_dram_size(struct dram_para_t *para)
{
    uint32_t colflag = 10, rowflag = 13;
    uint32_t i = 0;
    uint32_t count = 0;
    uint32_t offset1, offset2;

    para->col_width = colflag;
    para->row_width = rowflag;
    dram_para_setup(para);
    dram_scan_readpipe(para);

    for (i = 0; i < 32; i++)
    {
        DRAM_MEM[0x200 + i] = 0x11111111;
        DRAM_MEM[0x600 + i] = 0x22222222;
    }
    for (i = 0; i < 32; i++)
    {
        if (DRAM_MEM[0x200 + i] == 0x22222222)
            count++;
    }
    if (count == 32)
    {
        colflag = 9;
    }
    else
    {
        colflag = 10;
    }

    count = 0;
    para->col_width = colflag;
    para->row_width = rowflag;
    dram_para_setup(para);

    if (colflag == 10)
    {
        offset1 = 0x400000;
        offset2 = 0xC00000;
    }
    else
    {
        offset1 = 0x200000;
        offset2 = 0x600000;
    }
    for (i = 0; i < 32; i++)
    {
        DRAM_MEM[offset1 + i] = 0x33333333;
        DRAM_MEM[offset2 + i] = 0x44444444;
    }
    for (i = 0; i < 32; i++)
    {
        if(DRAM_MEM[offset1 + i] == 0x44444444)
        count++;
    }
    if (count == 32)
    {
        rowflag = 12;
    }
    else
    {
        rowflag = 13;
    }
    para->col_width = colflag;
    para->row_width = rowflag;
    if (para->row_width != 13)
    {
        para->size = 16;
    }
    else if (para->col_width == 10)
    {
        para->size = 64;
    }
    else
    {
        para->size = 32;
    }
    dram_set_autofresh_cycle(para->clk);
    para->access_mode = 0;
    dram_para_setup(para);

    return 0;
}

static int dram_init(struct dram_para_t * para)
{
	uint32_t val = 0;
	uint32_t i;

    GPIO_SetMode(&GPIO->PORTB, GPIO_PIN_3, PB3_MODE_DISABLED);
    
	dram_delay(5);
	if(((para->cas) >> 3) & 0x1)
	{
        GPIO->SDR_PAD_PUL = ( SDR_PAD_PUL_INTERNAL_REF_EN_ENABLE | (0x20 << SDR_PAD_PUL_REF_CONF_FACTOR_POS));
	}
	if((para->clk >= 144) && (para->clk <= 180))
	{
        GPIO->SDR_PAD_DRV = (SDR_PAD_DRV_RAS_CAS_MD_LEVEL_2|
                             SDR_PAD_DRV_DQS_MD_LEVEL_2 |
                             SDR_PAD_DRV_DQM_MD_LEVEL_2 |
                             SDR_PAD_DRV_DA_BA_MD_LEVEL_2 |
                             SDR_PAD_DRV_CK_MD_LEVEL_2 | 
                             SDR_PAD_DRV_DQ_MD_LEVEL_2);
	}
	if(para->clk >= 180)
	{
        GPIO->SDR_PAD_DRV = (SDR_PAD_DRV_RAS_CAS_MD_LEVEL_3 | 
                             SDR_PAD_DRV_DQS_MD_LEVEL_3 | 
                             SDR_PAD_DRV_DQM_MD_LEVEL_3 |
                             SDR_PAD_DRV_DA_BA_MD_LEVEL_3 | 
                             SDR_PAD_DRV_CK_MD_LEVEL_3 | 
                             SDR_PAD_DRV_DQ_MD_LEVEL_3);
	}
	if((para->clk) <= 96)
	{
		val = (0x1 << 0) | (0x0 << 4) | (((para->clk * 2) / 12 - 1) << 8) | (0x1u << 31);
	}
	else
	{
		val = (0x0 << 0) | (0x0 << 4) | (((para->clk * 2) / 24 - 1) << 8) | (0x1u << 31);
	}

	if(para->cas & (0x1 << 4))
	{
        CCU->PLL_DDR_PAT = (PLLDDR_PAT_CTRL_SIG_DELT_PAT_EN |
                            PLLDDR_PAT_CTRL_SPR_FREQ_TRIANGULAR |
                            PLLDDR_PAT_CTRL_WAVE_STEP(0x113) |
                            PLLDDR_PAT_CTRL_FREQ_31_5KHZ |
                            PLLDDR_DAT_CTRL_WAVE_BOT(0x3333));
	}
	else if(para->cas & (0x1 << 5))
	{
        CCU->PLL_DDR_PAT = (PLLDDR_PAT_CTRL_SIG_DELT_PAT_EN |
                            PLLDDR_PAT_CTRL_SPR_FREQ_TRIANGULAR |
                            PLLDDR_PAT_CTRL_WAVE_STEP(0xCE) |
                            PLLDDR_PAT_CTRL_FREQ_31_5KHZ |
                            PLLDDR_DAT_CTRL_WAVE_BOT(0x6666));
	}
	else if(para->cas & (0x1 << 6))
	{
        CCU->PLL_DDR_PAT = (PLLDDR_PAT_CTRL_SIG_DELT_PAT_EN |
                            PLLDDR_PAT_CTRL_SPR_FREQ_TRIANGULAR |
                            PLLDDR_PAT_CTRL_WAVE_STEP(0x89) |
                            PLLDDR_PAT_CTRL_FREQ_31_5KHZ |
                            PLLDDR_DAT_CTRL_WAVE_BOT(0x9999));
	}
	else if(para->cas & (0x1 << 7))
	{
        CCU->PLL_DDR_PAT = (PLLDDR_PAT_CTRL_SIG_DELT_PAT_EN |
                    PLLDDR_PAT_CTRL_SPR_FREQ_TRIANGULAR |
                    PLLDDR_PAT_CTRL_WAVE_STEP(0x44) |
                    PLLDDR_PAT_CTRL_FREQ_31_5KHZ |
                    PLLDDR_DAT_CTRL_WAVE_BOT(0xCCCC));
	}
	if(para->cas & (0xf << 4))
	{
		val |= 0x1 << 24;
	}
    CCU->PLL_DDR_CTRL = val;
    CCU->PLL_DDR_CTRL |= PLL_DDR_CTRL_CFG_UPDATE;
	while((CCU->PLL_DDR_CTRL & PLL_DDR_CTRL_LOCK_LOCKED) == 0);
	dram_delay(5);
    CCU->BUS_CLK_GATING_0 |= BUS_CLK_GATING_SDRAM_PASS_VAL;
    CCU->BUS_SOFT_RST_0 |= BUS_SOFT_RST_SDRAM_ASSERT_VAL;
	for(i = 0; i < 10; i++)
		continue;
    CCU->BUS_SOFT_RST_0 |= BUS_SOFT_RST_SDRAM_DEASSERT_VAL;

    (para->sdr_ddr == DRAM_TYPE_DDR) ? (GPIO->SDR_PAD_PUL |= (0x1 << SDR_PAD_PUL_SDRAM_PAD_TYPE_POS)) : (GPIO->SDR_PAD_PUL &= ~(0x1 << SDR_PAD_PUL_SDRAM_PAD_TYPE_POS));

	DRAM->STMG0R = (SDR_T_CAS << 0) | (SDR_T_RAS << 3) | (SDR_T_RCD << 7) | (SDR_T_RP << 10) | (SDR_T_WR << 13) | (SDR_T_RFC << 15) | (SDR_T_XSR << 19) | (SDR_T_RC << 28);
	DRAM->STMG1R = (SDR_T_INIT << 0) | (SDR_T_INIT_REF << 16) | (SDR_T_WTR << 20) | (SDR_T_RRD << 22) | (SDR_T_XP << 25);
	dram_para_setup(para);
	dram_check_type(para);

	(para->sdr_ddr == DRAM_TYPE_DDR) ? (GPIO->SDR_PAD_PUL |= (0x1 << SDR_PAD_PUL_SDRAM_PAD_TYPE_POS)) : (GPIO->SDR_PAD_PUL &= ~(0x1 << SDR_PAD_PUL_SDRAM_PAD_TYPE_POS));

	dram_set_autofresh_cycle(para->clk * 1000000);
	dram_scan_readpipe(para);
	dram_get_dram_size(para);

	for(i = 0; i < 128; i++)
	{
		*((volatile uint32_t *)(para->base + 4 * i)) = para->base + 4 * i;
	}

	for(i = 0; i < 128; i++)
	{
		if(*((volatile uint32_t *)(para->base + 4 * i)) != (para->base + 4 * i))
        {
            return 0;
        }

	}
	return 1;
}

void DRAM_Init(void)
{
	struct dram_para_t para;
    volatile uint32_t *dsz = (volatile uint32_t *)0x0000005c;

	para.base = 0x80000000;
	para.size = 32;
	para.clk = PLL_DDR_CLK / 1000000;
	para.access_mode = 1;
	para.cs_num = 1;
	para.ddr8_remap = 0;
	para.sdr_ddr = DRAM_TYPE_DDR;
	para.bwidth = 16;
	para.col_width = 10;
	para.row_width = 13;
	para.bank_size = 4;
	para.cas = 0x3;

	if((dsz[0] >> 24) == 'X')
    {
        return;
    }

	if(dram_init(&para))
    {
		dsz[0] = (((uint32_t)'X') << 24) | (para.size << 0);
    }
}