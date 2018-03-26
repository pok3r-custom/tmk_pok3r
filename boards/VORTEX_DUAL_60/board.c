/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)
/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {

};

#endif

#define FIRMWARE_ADDR 0x2c00

void nvic_set_vtor(uint32_t addr){
    addr &= 0x1fffff80;
    SCB->VTOR = addr;
}

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {
    // NVIC
    nvic_set_vtor(FIRMWARE_ADDR);
    
    // CKCU
    CKCU->LPCR = CKCU_LPCR_BKISO;           // Backup domain
    CKCU->APBCCR1 = CKCU_APBCCR1_BKPREN;    // Backup domain register access

    CKCU->AHBCFGR = 1;  // Set AHB prescaler (CK_AHB = CK_SYS / 2)

    // PLL
    CKCU->GCCR |= CKCU_GCCR_HSEEN;      // HSE enable
    CKCU->GCFGR &= ~CKCU_GCFGR_PLLSRC;  // PLL source HSE
    //CKCU->GCFGR |= CKCU_GCFGR_PLLSRC;   // PLL source HSI
    CKCU->PLLCFGR |= 18 << 23;          // PLL feedback divider = 18
    CKCU->PLLCFGR &= CKCU_PLLCFGR_POTD_MASK;    // PLL output divider = 1

    CKCU->GCCR |= CKCU_GCCR_PLLEN;           // PLL enable

    while(CKCU->GCSR & CKCU_GCSR_PLLRDY == 0);  // wait for PLL

    // system clock
    CKCU->GCCR &= ~CKCU_GCCR_SW_MASK;   // set clock source to PLL
    while(CKCU->CKST & CKCU_CKST_CKSWST_MASK != 0);      // wait for clock switch

//    while((REG_CKCU->CKST.HSEST & 2) == 0); // check HSE in use
//    while((REG_CKCU->CKST.PLLST & 1) == 0); // check PLL in use

//    while(REG_CKCU->CKST.HSIST != 0);   // check HSI not in use
//    REG_CKCU->GCCR.HSIEN = 0;           // HSI disable

//    REG_CKCU->AHBCCR.FMCEN = 1;
    FMC->CFCR = (FMC->CFCR & ~FMC_CFCR_WAIT_MASK) | FMC_CFCR_WAIT_2; // Flash wait status 2 (48MHz <= HCLK <= 72MHz)
}
