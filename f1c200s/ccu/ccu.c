#include "ccu.h"

void CCU_EnableBusClockGating_0(uint32_t peripheral)
{
    CCU->BUS_CLK_GATING_0 |= peripheral;
}

void CCU_EnableBusClockGating_1(uint32_t peripheral)
{
    CCU->BUS_CLK_GATING_1 |= peripheral;
}

void CCU_EnableBusClockGating_2(uint32_t peripheral)
{
    CCU->BUS_CLK_GATING_2 |= peripheral;
}

void CCU_DisableBusClockGating_0(uint32_t peripheral)
{
    CCU->BUS_CLK_GATING_0 &= peripheral;
}

void CCU_DisableBusClockGating_1(uint32_t peripheral)
{
    CCU->BUS_CLK_GATING_1 &= peripheral;
}

void CCU_DisableBusClockGating_2(uint32_t peripheral)
{
    CCU->BUS_CLK_GATING_2 &= peripheral;
}

uint32_t CCU_GetCPUFrequency(void)
{
    return 0;
}
