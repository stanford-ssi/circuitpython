/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 DeanM for Adafruit Industries
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
#include "shared-bindings/audiocore/Mixer.h"
#include "shared-bindings/audiocore/MixerVoice.h"

#include <stdint.h>

#include "lib/utils/context_manager_helpers.h"
#include "py/binary.h"
#include "py/objproperty.h"
#include "py/runtime.h"
#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/audiocore/RawSample.h"
#include "shared-bindings/util.h"
#include "supervisor/shared/translate.h"

//| .. currentmodule:: audiocore
//|
//| :class:`MixerVoice` -- Voice objects used with Mixer
//| =====================================================
//|
//| Used to access and control samples with `audiocore.Mixer`.
//|
//| .. class:: MixerVoice()
//|
//|   MixerVoice instance object(s) created by `audiocore.Mixer`.
//|
// TODO: support mono or stereo voices
STATIC mp_obj_t audioio_mixervoice_make_new(const mp_obj_type_t *type, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    audioio_mixervoice_obj_t *self = m_new_obj(audioio_mixervoice_obj_t);
    self->base.type = &audioio_mixervoice_type;

    common_hal_audioio_mixervoice_construct(self);

    return MP_OBJ_FROM_PTR(self);
}

//|   .. method:: play(sample, *, loop=False)
//|
//|     Plays the sample once when ``loop=False``, and continuously when ``loop=True``.
//|     Does not block. Use `playing` to block.
//|
//|     Sample must be an `audiocore.WaveFile`, `audiocore.Mixer` or `audiocore.RawSample`.
//|
//|     The sample must match the `audiocore.Mixer`'s encoding settings given in the constructor.
//|
STATIC mp_obj_t audioio_mixervoice_obj_play(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_sample, ARG_loop };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_sample,    MP_ARG_OBJ | MP_ARG_REQUIRED },
        { MP_QSTR_loop,      MP_ARG_BOOL | MP_ARG_KW_ONLY, {.u_bool = false} },
    };
    audioio_mixervoice_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    //raise_error_if_deinited(common_hal_audioio_mixervoice_deinited(self));
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_obj_t sample = args[ARG_sample].u_obj;
    common_hal_audioio_mixervoice_play(self, sample, args[ARG_loop].u_bool);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(audioio_mixervoice_play_obj, 1, audioio_mixervoice_obj_play);

//|   .. method:: stop()
//|
//|     Stops playback of the sample on this voice.
//|
STATIC mp_obj_t audioio_mixervoice_obj_stop(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_voice };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_voice, MP_ARG_INT, {.u_int = 0} },
    };
    audioio_mixervoice_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    //raise_error_if_deinited(common_hal_audioio_mixer_deinited(self));
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    common_hal_audioio_mixervoice_stop(self);

    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(audioio_mixervoice_stop_obj, 1, audioio_mixervoice_obj_stop);

//|   .. method:: level()
//|
//|     The volume level of a voice, as a floating point number between 0 and 1.
//|
STATIC mp_obj_t audioio_mixervoice_obj_get_level(mp_obj_t self_in) {
    return mp_obj_new_float(common_hal_audioio_mixervoice_get_level(self_in));
}
MP_DEFINE_CONST_FUN_OBJ_1(audioio_mixervoice_get_level_obj, audioio_mixervoice_obj_get_level);

STATIC mp_obj_t audioio_mixervoice_obj_set_level(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_level };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_level,     MP_ARG_OBJ | MP_ARG_REQUIRED },
    };
    audioio_mixervoice_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

	float level = mp_obj_get_float(args[ARG_level].u_obj);

    if (level > 1 || level < 0) {
        mp_raise_ValueError(translate("level must be between 0 and 1"));
    }

    common_hal_audioio_mixervoice_set_level(self, level);

    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(audioio_mixervoice_set_level_obj, 1, audioio_mixervoice_obj_set_level);

const mp_obj_property_t audioio_mixervoice_level_obj = {
    .base.type = &mp_type_property,
    .proxy = {(mp_obj_t)&audioio_mixervoice_get_level_obj,
              (mp_obj_t)&audioio_mixervoice_set_level_obj,
              (mp_obj_t)&mp_const_none_obj},
};

//TODO: @sommersoft - enable voice.playing tracking? will need an additional field
//      in the struct, with supporting logic. disabled documentation for now.

//   .. attribute:: playing
//
//     True when any voice is being output. (read-only)
//
STATIC mp_obj_t audioio_mixervoice_obj_get_playing(mp_obj_t self_in) {
#if 0
    audioio_mixer_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_bool(common_hal_audioio_mixer_get_playing(self));
#endif
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(audioio_mixervoice_get_playing_obj, audioio_mixervoice_obj_get_playing);

const mp_obj_property_t audioio_mixervoice_playing_obj = {
    .base.type = &mp_type_property,
    .proxy = {(mp_obj_t)&audioio_mixervoice_get_playing_obj,
              (mp_obj_t)&mp_const_none_obj,
              (mp_obj_t)&mp_const_none_obj},
};

STATIC const mp_rom_map_elem_t audioio_mixervoice_locals_dict_table[] = {
    // Methods
    { MP_ROM_QSTR(MP_QSTR_play), MP_ROM_PTR(&audioio_mixervoice_play_obj) },
    { MP_ROM_QSTR(MP_QSTR_stop), MP_ROM_PTR(&audioio_mixervoice_stop_obj) },

    // Properties
    { MP_ROM_QSTR(MP_QSTR_playing), MP_ROM_PTR(&audioio_mixervoice_playing_obj) },
    { MP_ROM_QSTR(MP_QSTR_level), MP_ROM_PTR(&audioio_mixervoice_level_obj) },
};
STATIC MP_DEFINE_CONST_DICT(audioio_mixervoice_locals_dict, audioio_mixervoice_locals_dict_table);

const mp_obj_type_t audioio_mixervoice_type = {
    { &mp_type_type },
    .name = MP_QSTR_MixerVoice,
    .make_new = audioio_mixervoice_make_new,
    .locals_dict = (mp_obj_dict_t*)&audioio_mixervoice_locals_dict,
};
