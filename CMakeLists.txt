## TMK-Pok3r CMakeLists.txt
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(TMK_Pok3r NONE)

### =================== SOURCES =================== ###

SET(FILES
    README.md

    Makefile
    Makefile.pok3r
    Makefile.pok3r_rgb
    Makefile.vortex_core

    chconf.h
    config.h
    halconf.h
    mcuconf.h

    keymap_common.h
    keymap_pok3r.c

    led_pok3r.c
    matrix_pok3r.c

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
    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x/ht32f1654.h
    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x/ht32f1655.h
    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x/ht32f165x_reg.h
    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x/ht32f1654_reg.h
    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x/ht32f1655_reg.h

    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/ld/HT32F1654.ld
    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/ld/HT32F1655.ld
    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/mk/startup_ht32f1654.mk
    ChibiOS-Contrib/os/common/startup/ARMCMx/compilers/GCC/mk/startup_ht32f1655.mk
    ChibiOS-Contrib/os/common/startup/ARMCMx/devices/HT32F1654/cmparams.h
    ChibiOS-Contrib/os/common/startup/ARMCMx/devices/HT32F1655/cmparams.h

    ChibiOS-Contrib/os/hal/ports/HT32/HT32F1654/platform.mk
    #ChibiOS-Contrib/os/hal/ports/HT32/HT32F1654/ht32_registry.h

    ChibiOS-Contrib/os/hal/ports/HT32/HT32F1655/platform.mk
    ChibiOS-Contrib/os/hal/ports/HT32/HT32F1655/ht32_registry.h

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

    tmk_core/common/command.c
    tmk_core/common/eeconfig.h
    tmk_core/common/chibios/eeconfig.c
    tmk_core/protocol/chibios/usb_main.c
)

INCLUDE_DIRECTORIES(
    .
    boards/VORTEX_DUAL_60
    ChibiOS/os/hal/include
    ChibiOS-Contrib/os/common/ext/CMSIS/HT32F165x
    ChibiOS-Contrib/os/common/startup/ARMCMx/devices/HT32F1655
    ChibiOS-Contrib/os/hal/ports/HT32/HT32F1655
    ChibiOS-Contrib/os/hal/ports/HT32/LLD
)

### =================== BUILD =================== ###

ADD_CUSTOM_TARGET(tmk-pok3r-dummy SOURCES ${FILES})

ADD_CUSTOM_TARGET(firmware ALL
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND make pok3r
    #COMMAND make -f Makefile.pok3r
    #COMMAND make -f Makefile.pok3r_rgb
    #COMMAND make -f Makefile.vortex_core
)
