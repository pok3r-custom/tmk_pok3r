## TMK-Pok3r CMakeLists.txt
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(TMK_POK3R NONE)

### =================== SOURCES =================== ###

SET(FILES
    README.md

    Makefile
    Makefile.app_pok3r
    Makefile.app_vortex_core
    Makefile.tmk_pok3r
    Makefile.tmk_pok3r_rgb
    Makefile.tmk_vortex_core

    chconf.h
    config.h
    halconf.h
    mcuconf.h

    keymap_common.h
    keymap_pok3r.c
    keymap_vortex_core.c

    led_pok3r.c
    led_vortex_core.c
    
    matrix_pok3r.c
    matrix_vortex_core.c

    apps/gd25q_flash.h
    apps/pok3r_main.c
    apps/pok3r_app.sym
    apps/vortex_core_main.c
    apps/vortex_core_app.sym

    boards/VORTEX_DUAL_60/board.mk
    boards/VORTEX_DUAL_60/board.h
    boards/VORTEX_DUAL_60/board.c

    boards/CYKB167_D_V03/board.mk
    boards/CYKB167_D_V03/board.h
    boards/CYKB167_D_V03/board.c

    boards/CYKB175_V03/board.mk
    boards/CYKB175_V03/board.h
    boards/CYKB175_V03/board.c

    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x/ht32f165x.h
    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x/ht32f165x_reg.h

    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/ld/HT32F1653.ld
    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/ld/HT32F1654.ld
    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/ld/HT32F1655.ld
    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/ld/HT32F1656.ld
    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/mk/startup_ht32f165x.mk
    ChibiOS-Contrib/os/common/startup/ARMCMx/devices/HT32F165x/cmparams.h

    ChibiOS-Contrib/os/hal/ports/HT32/HT32F165x/platform.mk
    ChibiOS-Contrib/os/hal/ports/HT32/HT32F165x/ht32_registry.h

    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_lld.h
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_lld.c
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_gpt_lld.h
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_gpt_lld.c
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_pal_lld.h
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_pal_lld.c
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_spi_lld.h
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_spi_lld.c
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_st_lld.h
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_st_lld.c
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_uart_lld.h
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_uart_lld.c
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_usb_lld.h
    ChibiOS-Contrib/os/hal/ports/HT32/LLD/hal_usb_lld.c

    tmk_core/tool/chibios/common.mk
    tmk_core/tool/chibios/chibios.mk

    tmk_core/common/command.c
    tmk_core/common/eeconfig.h
    tmk_core/common/chibios/eeconfig.c
    tmk_core/protocol/chibios/usb_main.c
)

INCLUDE_DIRECTORIES(
    .
    boards/VORTEX_DUAL_60
    #boards/CYKB175_V03
    ChibiOS/os/common/ports/ARMCMx
    ChibiOS/os/hal/include
    ChibiOS/os/hal/osal/rt
    ChibiOS/os/rt/include
    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x
    ChibiOS-Contrib/os/common/ports/ARMCMx
    ChibiOS-Contrib/os/common/startup/ARMCMx/devices/HT32F165x
    ChibiOS-Contrib/os/hal/include
    ChibiOS-Contrib/os/hal/osal/rt
    ChibiOS-Contrib/os/hal/ports/HT32/HT32F165x
    ChibiOS-Contrib/os/hal/ports/HT32/LLD
    ChibiOS-Contrib/os/rt/include
)


### =================== BUILD =================== ###

ADD_CUSTOM_TARGET(tmk-pok3r-dummy SOURCES ${FILES})

ADD_CUSTOM_TARGET(firmware ALL
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND make pok3r
    #COMMAND make vortex_core
)
