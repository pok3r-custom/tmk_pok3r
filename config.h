#ifndef CONFIG_H
#define CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0141
#define DEVICE_VER      0x0001

#define MANUFACTURER        "TMK"
#define USBSTR_MANUFACTURER 'T','\x00', 'M','\x00', 'K','\x00', ' ','\x00', '\xc6','\x00'
#define PRODUCT             "POK3R/TMK"
#define USBSTR_PRODUCT      'P','\x00', 'O','\x00', 'K','\x00', '3','\x00', 'R','\x00', '/','\x00', 'T','\x00', 'M','\x00', 'K','\x00'

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 7

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
