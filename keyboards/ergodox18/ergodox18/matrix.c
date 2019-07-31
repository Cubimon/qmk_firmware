/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "ergodox18.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_row(uint8_t row);
static void select_row(uint8_t row);


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

#define LED_ON()    do { palSetPad(TEENSY_PIN13_IOPORT, TEENSY_PIN13) ;} while (0)
#define LED_OFF()   do { palClearPad(TEENSY_PIN13_IOPORT, TEENSY_PIN13); } while (0)
#define LED_TGL()   do { palTogglePad(TEENSY_PIN13_IOPORT, TEENSY_PIN13); } while (0)

void matrix_init(void)
{
    debug_enable = true;
    debug_matrix = true;
    print("Entering matrix_init\n");
    // initialize row and col
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        unselect_row(i);
    }
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    LED_ON();
    wait_ms(100);
    LED_OFF();
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        wait_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_row(i);
    }

    if (debouncing) {
        if (--debouncing) {
            wait_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

/* Column pin configuration */
static void init_cols(void)
{
    // internal pull-up
    palSetPadMode(TEENSY_PIN0_IOPORT, TEENSY_PIN0, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN1_IOPORT, TEENSY_PIN1, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN2_IOPORT, TEENSY_PIN2, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN3_IOPORT, TEENSY_PIN3, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN4_IOPORT, TEENSY_PIN4, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN5_IOPORT, TEENSY_PIN5, PAL_MODE_INPUT_PULLUP);
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
    matrix_row_t result = 0;
    result |= (palReadPad(TEENSY_PIN0_IOPORT, TEENSY_PIN0) == PAL_HIGH) ? 0 : (1 << 0);
    result |= (palReadPad(TEENSY_PIN1_IOPORT, TEENSY_PIN1) == PAL_HIGH) ? 0 : (1 << 1);
    result |= (palReadPad(TEENSY_PIN2_IOPORT, TEENSY_PIN2) == PAL_HIGH) ? 0 : (1 << 2);
    result |= (palReadPad(TEENSY_PIN3_IOPORT, TEENSY_PIN3) == PAL_HIGH) ? 0 : (1 << 3);
    result |= (palReadPad(TEENSY_PIN4_IOPORT, TEENSY_PIN4) == PAL_HIGH) ? 0 : (1 << 4);
    result |= (palReadPad(TEENSY_PIN5_IOPORT, TEENSY_PIN5) == PAL_HIGH) ? 0 : (1 << 5);
    return result;
}

/* Row pin configuration */
static void unselect_row(uint8_t row)
{
    switch(row) {
        case 7:
            palSetPadMode(TEENSY_PIN6_IOPORT, TEENSY_PIN6, PAL_MODE_INPUT);
            break;
        case 8:
            palSetPadMode(TEENSY_PIN7_IOPORT, TEENSY_PIN7, PAL_MODE_INPUT);
            break;
        case 9:
            palSetPadMode(TEENSY_PIN8_IOPORT, TEENSY_PIN8, PAL_MODE_INPUT);
            break;
        case 10:
            palSetPadMode(TEENSY_PIN9_IOPORT, TEENSY_PIN9, PAL_MODE_INPUT);
            break;
        case 11:
            palSetPadMode(TEENSY_PIN10_IOPORT, TEENSY_PIN10, PAL_MODE_INPUT);
            break;
        case 12:
            palSetPadMode(TEENSY_PIN11_IOPORT, TEENSY_PIN11, PAL_MODE_INPUT);
            break;
        case 13:
            palSetPadMode(TEENSY_PIN12_IOPORT, TEENSY_PIN12, PAL_MODE_INPUT);
            break;
    }
}

static void select_row(uint8_t row)
{
    // Output low to select
    switch(row) {
        case 7:
            palSetPadMode(TEENSY_PIN6_IOPORT, TEENSY_PIN6, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN6_IOPORT, TEENSY_PIN6);
            break;
        case 8:
            palSetPadMode(TEENSY_PIN7_IOPORT, TEENSY_PIN7, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN7_IOPORT, TEENSY_PIN7);
            break;
        case 9:
            palSetPadMode(TEENSY_PIN8_IOPORT, TEENSY_PIN8, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN8_IOPORT, TEENSY_PIN8);
            break;
        case 10:
            palSetPadMode(TEENSY_PIN9_IOPORT, TEENSY_PIN9, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN9_IOPORT, TEENSY_PIN9);
            break;
        case 11:
            palSetPadMode(TEENSY_PIN10_IOPORT, TEENSY_PIN10, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN10_IOPORT, TEENSY_PIN10);
            break;
        case 12:
            palSetPadMode(TEENSY_PIN11_IOPORT, TEENSY_PIN11, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN11_IOPORT, TEENSY_PIN11);
            break;
        case 13:
            palSetPadMode(TEENSY_PIN12_IOPORT, TEENSY_PIN12, PAL_MODE_OUTPUT_PUSHPULL);
            palClearPad(TEENSY_PIN12_IOPORT, TEENSY_PIN12);
            break;
    }
}
