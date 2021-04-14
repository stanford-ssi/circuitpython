/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Lucian Copeland for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MICROPY_INCLUDED_ESP32S2_COMMON_HAL_DISPLAYIO_PARALLELBUS_H
#define MICROPY_INCLUDED_ESP32S2_COMMON_HAL_DISPLAYIO_PARALLELBUS_H

#include "common-hal/digitalio/DigitalInOut.h"

typedef struct {
    mp_obj_base_t base;
    uint32_t *bus; // pointer where 8 bits of data are written to the display
    digitalio_digitalinout_obj_t command;
    digitalio_digitalinout_obj_t chip_select;
    digitalio_digitalinout_obj_t reset;
    digitalio_digitalinout_obj_t write;
    digitalio_digitalinout_obj_t read;
    uint8_t data0_pin; // pin number for the lowest number data pin.  Must be 8-bit aligned
    bool data_write_same_register; // if data and write pins are in the sare
    uint32_t *write_set_register; // pointer to the write group for setting the write bit to latch the data on the LCD
    uint32_t *write_clear_register; // pointer to the write group for clearing the write bit to latch the data on the LCD
    uint32_t write_mask; // bit mask for the single bit for the write pin register
} displayio_parallelbus_obj_t;

#endif // MICROPY_INCLUDED_ESP32S2_COMMON_HAL_DISPLAYIO_PARALLELBUS_H
