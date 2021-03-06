// Copyright (c) 2014 Paul Sokolovsky
// SPDX-FileCopyrightText: 2014 MicroPython & CircuitPython contributors (https://github.com/adafruit/circuitpython/graphs/contributors)
//
// SPDX-License-Identifier: MIT

#include <assert.h>
#include <string.h>

#include "py/runtime.h"

#include "supervisor/shared/translate.h"

#if MICROPY_PY_UHASHLIB

#if MICROPY_PY_UHASHLIB_SHA256

#if MICROPY_SSL_MBEDTLS
#include "mbedtls/sha256.h"
#else
#include "crypto-algorithms/sha256.h"
#endif

#endif

#if MICROPY_PY_UHASHLIB_SHA1

#if MICROPY_SSL_AXTLS
#include "lib/axtls/crypto/crypto.h"
#endif

#if MICROPY_SSL_MBEDTLS
#include "mbedtls/sha1.h"
#endif

#endif


typedef struct _mp_obj_hash_t {
    mp_obj_base_t base;
    char state[0];
} mp_obj_hash_t;

#if MICROPY_PY_UHASHLIB_SHA256
STATIC mp_obj_t uhashlib_sha256_update(mp_obj_t self_in, mp_obj_t arg);

#if MICROPY_SSL_MBEDTLS

STATIC mp_obj_t uhashlib_sha256_make_new(const mp_obj_type_t *type, size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    mp_arg_check_num(n_args, kw_args, 0, 1, false);
    mp_obj_hash_t *o = m_new_obj_var(mp_obj_hash_t, char, sizeof(mbedtls_sha256_context));
    o->base.type = type;
    mbedtls_sha256_init((mbedtls_sha256_context *)&o->state);
    mbedtls_sha256_starts((mbedtls_sha256_context *)&o->state, 0);
    if (n_args == 1) {
        uhashlib_sha256_update(MP_OBJ_FROM_PTR(o), args[0]);
    }
    return MP_OBJ_FROM_PTR(o);
}

STATIC mp_obj_t uhashlib_sha256_update(mp_obj_t self_in, mp_obj_t arg) {
    mp_obj_hash_t *self = MP_OBJ_TO_PTR(self_in);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(arg, &bufinfo, MP_BUFFER_READ);
    mbedtls_sha256_update((mbedtls_sha256_context *)&self->state, bufinfo.buf, bufinfo.len);
    return mp_const_none;
}

STATIC mp_obj_t uhashlib_sha256_digest(mp_obj_t self_in) {
    mp_obj_hash_t *self = MP_OBJ_TO_PTR(self_in);
    vstr_t vstr;
    vstr_init_len(&vstr, 32);
    mbedtls_sha256_finish((mbedtls_sha256_context *)&self->state, (unsigned char *)vstr.buf);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}

#else

static void check_not_unicode(const mp_obj_t arg) {
    #if MICROPY_CPYTHON_COMPAT
    if (MP_OBJ_IS_STR(arg)) {
        mp_raise_TypeError(translate("a bytes-like object is required"));
    }
    #endif
}

STATIC mp_obj_t uhashlib_sha256_make_new(const mp_obj_type_t *type, size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    mp_arg_check_num(n_args, kw_args, 0, 1, false);
    mp_obj_hash_t *o = m_new_obj_var(mp_obj_hash_t, char, sizeof(CRYAL_SHA256_CTX));
    o->base.type = type;
    sha256_init((CRYAL_SHA256_CTX *)o->state);
    if (n_args == 1) {
        uhashlib_sha256_update(MP_OBJ_FROM_PTR(o), args[0]);
    }
    return MP_OBJ_FROM_PTR(o);
}

STATIC mp_obj_t uhashlib_sha256_update(mp_obj_t self_in, mp_obj_t arg) {
    check_not_unicode(arg);
    mp_obj_hash_t *self = MP_OBJ_TO_PTR(self_in);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(arg, &bufinfo, MP_BUFFER_READ);
    sha256_update((CRYAL_SHA256_CTX *)self->state, bufinfo.buf, bufinfo.len);
    return mp_const_none;
}

STATIC mp_obj_t uhashlib_sha256_digest(mp_obj_t self_in) {
    mp_obj_hash_t *self = MP_OBJ_TO_PTR(self_in);
    vstr_t vstr;
    vstr_init_len(&vstr, SHA256_BLOCK_SIZE);
    sha256_final((CRYAL_SHA256_CTX *)self->state, (byte *)vstr.buf);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}
#endif

STATIC MP_DEFINE_CONST_FUN_OBJ_2(uhashlib_sha256_update_obj, uhashlib_sha256_update);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(uhashlib_sha256_digest_obj, uhashlib_sha256_digest);

STATIC const mp_rom_map_elem_t uhashlib_sha256_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_update), MP_ROM_PTR(&uhashlib_sha256_update_obj) },
    { MP_ROM_QSTR(MP_QSTR_digest), MP_ROM_PTR(&uhashlib_sha256_digest_obj) },
};

STATIC MP_DEFINE_CONST_DICT(uhashlib_sha256_locals_dict, uhashlib_sha256_locals_dict_table);

STATIC const mp_obj_type_t uhashlib_sha256_type = {
    { &mp_type_type },
    .name = MP_QSTR_sha256,
    .make_new = uhashlib_sha256_make_new,
    .locals_dict = (void *)&uhashlib_sha256_locals_dict,
};
#endif

#if MICROPY_PY_UHASHLIB_SHA1
STATIC mp_obj_t uhashlib_sha1_update(mp_obj_t self_in, mp_obj_t arg);

#if MICROPY_SSL_AXTLS
STATIC mp_obj_t uhashlib_sha1_make_new(const mp_obj_type_t *type, size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    mp_arg_check_num(n_args, kw_args, 0, 1, false);
    mp_obj_hash_t *o = m_new_obj_var(mp_obj_hash_t, char, sizeof(SHA1_CTX));
    o->base.type = type;
    SHA1_Init((SHA1_CTX *)o->state);
    if (n_args == 1) {
        uhashlib_sha1_update(MP_OBJ_FROM_PTR(o), args[0]);
    }
    return MP_OBJ_FROM_PTR(o);
}

STATIC mp_obj_t uhashlib_sha1_update(mp_obj_t self_in, mp_obj_t arg) {
    check_not_unicode(arg);
    mp_obj_hash_t *self = MP_OBJ_TO_PTR(self_in);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(arg, &bufinfo, MP_BUFFER_READ);
    SHA1_Update((SHA1_CTX *)self->state, bufinfo.buf, bufinfo.len);
    return mp_const_none;
}

STATIC mp_obj_t uhashlib_sha1_digest(mp_obj_t self_in) {
    mp_obj_hash_t *self = MP_OBJ_TO_PTR(self_in);
    vstr_t vstr;
    vstr_init_len(&vstr, SHA1_SIZE);
    SHA1_Final((byte *)vstr.buf, (SHA1_CTX *)self->state);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}
#endif

#if MICROPY_SSL_MBEDTLS
STATIC mp_obj_t uhashlib_sha1_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 0, 1, false);
    mp_obj_hash_t *o = m_new_obj_var(mp_obj_hash_t, char, sizeof(mbedtls_sha1_context));
    o->base.type = type;
    mbedtls_sha1_init((mbedtls_sha1_context *)o->state);
    mbedtls_sha1_starts((mbedtls_sha1_context *)o->state);
    if (n_args == 1) {
        uhashlib_sha1_update(MP_OBJ_FROM_PTR(o), args[0]);
    }
    return MP_OBJ_FROM_PTR(o);
}

STATIC mp_obj_t uhashlib_sha1_update(mp_obj_t self_in, mp_obj_t arg) {
    mp_obj_hash_t *self = MP_OBJ_TO_PTR(self_in);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(arg, &bufinfo, MP_BUFFER_READ);
    mbedtls_sha1_update((mbedtls_sha1_context *)self->state, bufinfo.buf, bufinfo.len);
    return mp_const_none;
}

STATIC mp_obj_t uhashlib_sha1_digest(mp_obj_t self_in) {
    mp_obj_hash_t *self = MP_OBJ_TO_PTR(self_in);
    vstr_t vstr;
    vstr_init_len(&vstr, 20);
    mbedtls_sha1_finish((mbedtls_sha1_context *)self->state, (byte *)vstr.buf);
    mbedtls_sha1_free((mbedtls_sha1_context *)self->state);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}
#endif

STATIC MP_DEFINE_CONST_FUN_OBJ_2(uhashlib_sha1_update_obj, uhashlib_sha1_update);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(uhashlib_sha1_digest_obj, uhashlib_sha1_digest);

STATIC const mp_rom_map_elem_t uhashlib_sha1_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_update), MP_ROM_PTR(&uhashlib_sha1_update_obj) },
    { MP_ROM_QSTR(MP_QSTR_digest), MP_ROM_PTR(&uhashlib_sha1_digest_obj) },
};
STATIC MP_DEFINE_CONST_DICT(uhashlib_sha1_locals_dict, uhashlib_sha1_locals_dict_table);

STATIC const mp_obj_type_t uhashlib_sha1_type = {
    { &mp_type_type },
    .name = MP_QSTR_sha1,
    .make_new = uhashlib_sha1_make_new,
    .locals_dict = (void *)&uhashlib_sha1_locals_dict,
};
#endif

STATIC const mp_rom_map_elem_t mp_module_uhashlib_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_hashlib) },
    #if MICROPY_PY_UHASHLIB_SHA256
    { MP_ROM_QSTR(MP_QSTR_sha256), MP_ROM_PTR(&uhashlib_sha256_type) },
    #endif
    #if MICROPY_PY_UHASHLIB_SHA1
    { MP_ROM_QSTR(MP_QSTR_sha1), MP_ROM_PTR(&uhashlib_sha1_type) },
    #endif
};

STATIC MP_DEFINE_CONST_DICT(mp_module_uhashlib_globals, mp_module_uhashlib_globals_table);

const mp_obj_module_t mp_module_uhashlib = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&mp_module_uhashlib_globals,
};

#if MICROPY_PY_UHASHLIB_SHA256
#include "crypto-algorithms/sha256.c"
#endif

#endif // MICROPY_PY_UHASHLIB
