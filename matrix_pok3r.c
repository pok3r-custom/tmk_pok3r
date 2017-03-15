#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"

static matrix_row_t matrix[MATRIX_ROWS];

void matrix_init(void){
    memset(matrix, 0, MATRIX_ROWS);
}

uint8_t matrix_scan(void){

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col){
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row){
    return matrix[row];
}

void matrix_print(void)
{
    xprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: ");
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                xprintf("1");
            else
                xprintf("0");
        }
        xprintf("\n");
    }
}
