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

void nvic_set_vtor(u32 addr){
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
    CKCU->LPCR.BKISO = 1;       // Backup domain
    CKCU->APBCCR1.BKPREN = 1;   // Backup domain register access

    CKCU->AHBCFGR.AHBPRE = 1;   // Set AHB prescaler (CK_AHB = CK_SYS / 2)

    // PLL
    CKCU->GCCR.HSEEN = 1;           // HSE enable
    CKCU->GCFGR.PLLSRC = 0;         // PLL source HSE
//    CKCU->GCFGR.PLLSRC = 1;         // PLL source HSI
    CKCU->PLLCFGR.PFBD = 18;        // PLL feedback divider = 18
    CKCU->PLLCFGR.POTD = 0;         // PLL output divider = 1

    CKCU->GCCR.PLLEN = 1;           // PLL enable

    while(CKCU->GCSR.PLLRDY == 0);  // wait for PLL

    // system clock
    CKCU->GCCR.SW = 1;              // set clock source to PLL
    while(CKCU->CKST.CKSWST != 1);  // wait for clock switch

//    while((REG_CKCU->CKST.HSEST & 2) == 0); // check HSE in use
//    while((REG_CKCU->CKST.PLLST & 1) == 0); // check PLL in use

//    while(REG_CKCU->CKST.HSIST != 0);   // check HSI not in use
//    REG_CKCU->GCCR.HSIEN = 0;           // HSI disable

//    REG_CKCU->AHBCCR.FMCEN = 1;
    FMC->CFCR.WAIT = 3;             // Flash wait status 2 (48MHz <= HCLK <= 72MHz)
    
    
}
