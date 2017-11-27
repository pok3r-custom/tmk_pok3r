
#include "ch.h"
#include "hal.h"

#include "gd25q_flash.h"

u32 strlen(const char *str){
    u32 i = 0;
    while(*str++)
        ++i;
    return i;
}

u8 utox(u32 num, char *str){
    char tmp[8];
    int i = 0;
    while(num){
        tmp[i++] = "0123456789abcdef"[num & 0xf];
        num >>= 4;
    }
    for(int j = i-1; j >= 0; --j){
        *(str++) = tmp[j];
    }
    *str = 0;
    return i;
}

typedef enum {
    PIN_INPUT = 0,
    PIN_OUTPUT,
} PinDir;

typedef enum {
    DRIVE_4mA = 0,
    DRIVE_8mA,
} DriveMode;

typedef enum {
    PULL_DISABLE = 0,
    PULL_UP,
    PULL_DOWN,
} PullMode;

void nvic_enable_intr(u8 num){
    u8 off = num >> 5;
    u32 mask = 1 << (num & 0x1f);
    NVIC->ISER[off] = mask;
}

void nvic_disable_intr(u8 num){
    u8 off = num >> 5;
    u32 mask = 1 << (num & 0x1f);
    NVIC->ICER[off] = mask;
}

void ckcu_clock_enable(u32 clock, int en){
    u32 *reg;
    switch(clock >> 28){
        case 1:
            reg = &(CKCU->AHBCCR.word);
            break;
        case 2:
            reg = &(CKCU->APBCCR0.word);
            break;
        case 3:
            reg = &(CKCU->APBCCR1.word);
            break;
        default:
            return;
    }

    u32 mask = clock & 0x0FFFFFFFU;
    u32 bits = *reg;
    if(en)
        bits |= mask;
    else
        bits &= ~mask;
    *reg = bits;
}

void ckcu_clocks_enable(int ahb_mask, int apb0_mask, int apb1_mask, int en){
    u32 ahb = CKCU->AHBCCR.word;
    u32 apb0 = CKCU->APBCCR0.word;
    u32 apb1 = CKCU->APBCCR1.word;

    ahb &= ~ahb_mask;
    apb0 &= ~apb0_mask;
    apb1 &= ~apb1_mask;

    if(en){
        ahb |= ahb_mask;
        apb0 |= apb0_mask;
        apb1 |= apb1_mask;
    }

    CKCU->AHBCCR.word = ahb;
    CKCU->APBCCR0.word = apb0;
    CKCU->APBCCR1.word = apb1;
}

void afio_pin_config(int port, int pin, int function){
    const u8 shift = (pin & 0x7) << 2;
    if(pin >= 8){
        AFIO->GPnCFG[port].HR.word &= ~(0xf << shift);
        AFIO->GPnCFG[port].HR.word |= (function << shift);
    } else {
        AFIO->GPnCFG[port].LR.word &= ~(0xf << shift);
        AFIO->GPnCFG[port].LR.word |= (function << shift);
    }
}

void afio_init(void){
    // enable AFIO clock
    ckcu_clock_enable(CLOCK_AFIO, 1);
    // enable GPIO A clock
    ckcu_clock_enable(CLOCK_PA, 1);
    ckcu_clock_enable(CLOCK_PB, 1);
    ckcu_clock_enable(CLOCK_PC, 1);

//    gpio_pin_input_enable(GPIO_A, 14, 0);
//    gpio_pin_pull(GPIO_A, 14, PULL_DISABLE);
//    gpio_pin_input_enable(GPIO_A, 15, 0);
//    gpio_pin_pull(GPIO_A, 15, PULL_DISABLE);

//    gpio_pin_input_enable(GPIO_A, 11, 0);
//    gpio_pin_pull(GPIO_A, 11, PULL_DISABLE);

    afio_pin_config(GPIO_A, 11, AFIO_GPIO);
    afio_pin_config(GPIO_C, 13, AFIO_GPIO);

    afio_pin_config(GPIO_C, 14, AFIO_GPIO);
    afio_pin_config(GPIO_C, 15, AFIO_GPIO);

    // check HSEEN
    if(CKCU->GCCR.HSEEN == 0){
        afio_pin_config(GPIO_B, 14, AFIO_GPIO);
        afio_pin_config(GPIO_B, 15, AFIO_GPIO);
    }

    // disable GPIO A clock
//    ckcu_clock_enable(CLOCK_PA, 0);

    // CKOUT on PA8
//    afio_pin_config(GPIO_A, 8, AFIO_OTHER);
//    REG_CKCU->GCFGR.CKOUTSRC = 1;   // CKOUTSR = CCK_AHB / 16
//    REG_CKCU->GCFGR.CKOUTSRC = 2;   // CKOUTSR = CCK_SYS / 16

    // USART on PA8
    afio_pin_config(GPIO_A, 8, AFIO_USART);
}

void pinmux_spi(void){
    gpio_pin_direction(GPIO_B, 10, PIN_OUTPUT);
    gpio_pin_pull(GPIO_B, 10, PULL_DISABLE);
    // Select AF5 (SPI) for GPIO B pins 7,8,9 (LQFP-64 pins 58,59,60)
    afio_pin_config(GPIO_B, 7, 5);
    afio_pin_config(GPIO_B, 8, 5);
    afio_pin_config(GPIO_B, 9, 5);
}

void spi_init(void){
    ckcu_clock_enable(CLOCK_PB, 1);
    ckcu_clock_enable(CLOCK_AFIO, 1);
    // enable SPI1 clock
    ckcu_clock_enable(CLOCK_SPI1, 1);

    // chip select high
    gpio_pin_set_reset(GPIO_B, 10, 1);
    gpio_pin_direction(GPIO_B, 10, PIN_OUTPUT);

//    gpio_pin_pull(GPIO_B, 10, PULL_DISABLE);
//    gpio_pin_pull(GPIO_B, 10, PULL_UP);
//    gpio_pin_drive(GPIO_B, 10, DRIVE_8mA);

//    gpio_pin_drive(GPIO_B, 7, DRIVE_8mA);
//    gpio_pin_drive(GPIO_B, 8, DRIVE_8mA);
//    gpio_pin_drive(GPIO_B, 9, DRIVE_8mA);

    // pinmux spi pins
    afio_pin_config(GPIO_B, 7, 5);
    afio_pin_config(GPIO_B, 8, 5);
    afio_pin_config(GPIO_B, 9, 5);

    SPI1->SPICR1.SELM = 0;     // software chip select
    SPI1->SPICR1.SELAP = 0;    // active low

    SPI1->SPICR1.DFL = 8;      // 8 bits
    SPI1->SPICR1.FORMAT = 1;   // clock low, first edge
    SPI1->SPICR1.FIRSTBIT = 0; // msb first
    SPI1->SPICR1.MODE = 1;     // master mode

    SPI1->SPICPR.CP = 1;       // prescaler

    SPI1->SPIFCR.FIFOEN = 1;   // fifo enable
    SPI1->SPIFCR.RXFTLS = 4;
    SPI1->SPIFCR.TXFTLS = 4;

    SPI1->SPICR0.SELOEN = 1;   // chip select output
    SPI1->SPICR0.SPIEN = 1;    // enable
}

u8 spi_txrx(u8 byte){
    // wait for tx empty
    while(SPI1->SPISR.TXBE == 0);
    // send byte
    SPI1->SPIDR.DR = byte;
    // wait for rx data
    while(SPI1->SPISR.RXBNE == 0);
    // recv byte
    u32 data = SPI1->SPIDR.DR;
    return data & 0xFF;
}

void spi_flash_command(const u8 *cmd, int writelen, u8 *out, int readlen){
    // chip select low
    gpio_pin_set_reset(GPIO_B, 10, 0);

//    // Send command bytes
//    for(int i = 0; i < writelen; ++i){
//        spi_txrx(cmd[i]);
//    }

//    // Recv bytes
//    for(int i = 0; i < readlen; ++i){
//        out[i] = spi_txrx(0);
//    }

    int wlen = 0;
    while(wlen < writelen){
        int len = MIN(writelen - wlen, 8);
        // Send command bytes
        for(int i = 0; i < len; ++i){
            SPI1->SPIDR.word = cmd[wlen++];
        }
        // Read dummy data
        for(int i = 0; i < len; ++i){
            // wait for recv data
            while(SPI1->SPIFSR.RXFS == 0);
            // read/discard data
            SPI1->SPIDR.word;  // this only works in C
        }
    }

    int rlen = 0;
    while(rlen < readlen){
        int len = MIN(readlen - rlen, 8);
        // Send dummy bytes
        for(int i = 0; i < len; ++i){
            SPI1->SPIDR.word = 0;
        }
        // Read data
        for(int i = 0; i < len; ++i){
            // wait for recv data
            while(SPI1->SPIFSR.RXFS == 0);
            // read data
            u32 data = SPI1->SPIDR.word;
            out[rlen++] = data & 0xFF;
        }
    }

    // chip select high
    gpio_pin_set_reset(GPIO_B, 10, 1);
}

u8 flash_id[16];
u8 flash_mid[16];
u8 flash_data[0x400];

void spi_read(void){
//    pinmux_spi();

    u8 cmd[4];

    cmd[0] = GD25Q_RDID;
    spi_flash_command(cmd, 1, flash_id, 3);

    cmd[0] = GD25Q_REMS;
    cmd[1] = 0;
    cmd[2] = 0;
    cmd[3] = 0;
    spi_flash_command(cmd, 4, flash_mid, 2);

    u32 addr = 0;
//    u32 addr = 0xff0;
    cmd[0] = GD25Q_READ;
    cmd[1] = (addr >> 16) & 0xFF;
    cmd[2] = (addr >> 8) & 0xFF;
    cmd[3] = addr & 0xFF;
    spi_flash_command(cmd, 4, flash_data, 0x400);
}

#define VERSION_ADDR 0x2800

void flash_version_clear(){
    FMC->TADR.TADB = VERSION_ADDR;
    FMC->OCMR.CMD = OCMR_PAGE_ERASE;
    FMC->OPCR.OPM = OPCR_COMMIT;

    while(FMC->OPCR.OPM != OPCR_FINISHED);
}

void usart_init(void){
    // USART0 clock
    ckcu_clock_enable(CLOCK_USR0, 1);

    USART0->MDR.MODE = 0;   // normal operation
    USART0->DLR.BRD = 625;  // 115200 baud
    USART0->LCR.WLS = 1;    // 8 bits
    USART0->LCR.PBE = 0;    // no parity
    USART0->LCR.NSB = 0;    // 1 stop bit
    USART0->FCR.URRXEN = 0; // RX disable
    USART0->FCR.URTXEN = 1; // TX enable
}

void usart_write(const u8 *data, u32 size){
    while(size > 0){
        USART0->TBR.TD = *data;         // write fifo
        while(!(USART0->LSR.TXEMPT));   // wait while tx not empty
        data++;
        size--;
    }
}

void usart_log(const char *str){
    usart_write((const u8 *)str, strlen(str));
    usart_write((const u8 *)"\r\n", 2);
}

int main(void){
    // HAL Init
    halInit();
    
    // Clear the version so the board resets to the bootloader
    flash_version_clear();

    // I/O init
    afio_init();

//    spi_init();
//    spi_read();

    usart_init();
    
    usart_log("POK3R Boot");
    
    usart_log("TEST");

    // USB
//    usb_init();
//    usb_init_descriptors();
//    usb_callback_suspend(on_suspend);
//    usb_callback_configuration(on_configuration);

    // Enable D+ pull-up
//    usb_pull_up(1);

    u32 count = 0;
    while(1){
        count = count + 1;
//        wdt_reload();
    }

    return 0;
}