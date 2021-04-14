/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Dan Halbertfor Adafruit Industries
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

#include <stdint.h>

#include "py/obj.h"
#include "py/runtime.h"

#include "shared-bindings/usb_cdc/__init__.h"
#include "shared-bindings/usb_cdc/Serial.h"

#include "py/runtime.h"

//| """USB CDC Serial streams
//|
//| The `usb_cdc` module allows access to USB CDC (serial) communications."""
//|
//| serials: Tuple[Serial, ...]
//| """Tuple of all CDC streams. Each item is a `Serial`.
//| ``serials[0]`` is the USB REPL connection.
//| ``serials[1]`` is a second USB serial connection, unconnected to the REPL.
//| """
//|

static const mp_map_elem_t usb_cdc_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_usb_cdc) },
    { MP_ROM_QSTR(MP_QSTR_Serial),   MP_OBJ_FROM_PTR(&usb_cdc_serial_type) },
    { MP_ROM_QSTR(MP_QSTR_serials),  MP_OBJ_FROM_PTR(&usb_cdc_serials_tuple) },
};

static MP_DEFINE_CONST_DICT(usb_cdc_module_globals, usb_cdc_module_globals_table);

const mp_obj_module_t usb_cdc_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&usb_cdc_module_globals,
};
