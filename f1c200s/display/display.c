#include "display.h"
#include "../ccu/ccu.h"

void DISPLAY_Init()
{
    // enable clock for LCD
    CCU->BUS_CLK_GATING_1 |= (CCU_BUS_CLK_GATING_1_LCD | CCU_BUS_CLK_GATING_1_DEBE | CCU_BUS_CLK_GATING_1_DEFE);
    CCU->BUS_SOFT_RST_1   &= ~(CCU_BUS_SOFT_RST_1_LCD | CCU_BUS_SOFT_RST_1_DEBE | CCU_BUS_SOFT_RST_1_DEFE);
    CCU->BUS_SOFT_RST_1   |= (CCU_BUS_SOFT_RST_1_LCD | CCU_BUS_SOFT_RST_1_DEBE | CCU_BUS_SOFT_RST_1_DEFE);

    
    TCON->CTRL |= TCON_CTRL_MODULE_EN;  // enable module
}