// SPDX-FileCopyrightText: Copyright (c) 2013-2015 Damien P. George
// SPDX-FileCopyrightText: 2014 MicroPython & CircuitPython contributors (https://github.com/adafruit/circuitpython/graphs/contributors)
//
// SPDX-License-Identifier: MIT

// options to control how MicroPython is built

#define MICROPY_ALLOC_PATH_MAX      (PATH_MAX)
#define MICROPY_PERSISTENT_CODE_LOAD (0)
#define MICROPY_PERSISTENT_CODE_SAVE (1)

#if !defined(MICROPY_PERSISTENT_CODE_SAVE_FILE)
#if defined(__i386__) || defined(__x86_64__) || defined(_WIN32) || defined(__unix__) || defined(__APPLE__)
#define MICROPY_PERSISTENT_CODE_SAVE_FILE (1)
#else
#define MICROPY_PERSISTENT_CODE_SAVE_FILE (0)
#endif
#endif

#define MICROPY_EMIT_X64            (0)
#define MICROPY_EMIT_X86            (0)
#define MICROPY_EMIT_THUMB          (0)
#define MICROPY_EMIT_INLINE_THUMB   (0)
#define MICROPY_EMIT_INLINE_THUMB_ARMV7M (0)
#define MICROPY_EMIT_INLINE_THUMB_FLOAT (0)
#define MICROPY_EMIT_ARM            (0)

#define MICROPY_DYNAMIC_COMPILER    (1)
#define MICROPY_COMP_CONST_FOLDING  (1)
#define MICROPY_COMP_MODULE_CONST   (1)
#define MICROPY_COMP_CONST          (1)
#define MICROPY_COMP_DOUBLE_TUPLE_ASSIGN (1)
#define MICROPY_COMP_TRIPLE_TUPLE_ASSIGN (1)
#define MICROPY_COMP_RETURN_IF_EXPR (1)

#define MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE (0)

#define MICROPY_READER_POSIX        (1)
#define MICROPY_ENABLE_RUNTIME      (0)
#define MICROPY_ENABLE_GC           (1)
#define MICROPY_STACK_CHECK         (1)
#define MICROPY_HELPER_LEXER_UNIX   (1)
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_MPZ)
#define MICROPY_ENABLE_SOURCE_LINE  (1)
#define MICROPY_ENABLE_DOC_STRING   (0)
#define MICROPY_ERROR_REPORTING     (MICROPY_ERROR_REPORTING_DETAILED)
#define MICROPY_WARNINGS            (1)

#define MICROPY_FLOAT_IMPL          (MICROPY_FLOAT_IMPL_DOUBLE)
#define MICROPY_CPYTHON_COMPAT      (1)
#define MICROPY_PY_ASYNC_AWAIT      (1)
#define MICROPY_USE_INTERNAL_PRINTF (0)

#define MICROPY_PY_BUILTINS_STR_UNICODE (1)

// Define to 1 to use undertested inefficient GC helper implementation
// (if more efficient arch-specific one is not available).
#ifndef MICROPY_GCREGS_SETJMP
    #ifdef __mips__
        #define MICROPY_GCREGS_SETJMP (1)
    #else
        #define MICROPY_GCREGS_SETJMP (0)
    #endif
#endif

#define MICROPY_PY___FILE__         (0)
#define MICROPY_PY_ARRAY            (0)
#define MICROPY_PY_ATTRTUPLE        (0)
#define MICROPY_PY_COLLECTIONS      (0)
#define MICROPY_PY_MATH             (0)
#define MICROPY_PY_CMATH            (0)
#define MICROPY_PY_GC               (0)
#define MICROPY_PY_IO               (0)
#define MICROPY_PY_SYS              (0)

// MINGW only handles these errno names.
#ifdef __MINGW32__
#define MICROPY_PY_UERRNO_LIST \
  X(EPERM) \
  X(ENOENT) \
  X(ESRCH) \
  X(EINTR) \
  X(EIO) \
  X(ENXIO) \
  X(E2BIG) \
  X(ENOEXEC) \
  X(EBADF) \
  X(ECHILD) \
  X(EAGAIN) \
  X(ENOMEM) \
  X(EACCES) \
  X(EFAULT) \
  X(EBUSY) \
  X(EEXIST) \
  X(EXDEV) \
  X(ENODEV) \
  X(ENOTDIR) \
  X(EISDIR) \
  X(EINVAL) \
  X(ENFILE) \
  X(EMFILE) \
  X(ENOTTY) \
  X(EFBIG) \
  X(ENOSPC) \
  X(ESPIPE) \
  X(EROFS) \
  X(EMLINK) \
  X(EPIPE) \
  X(EDOM) \
  X(ERANGE) \
  X(EDEADLOCK) \
  X(EDEADLK) \
  X(ENAMETOOLONG) \
  X(ENOLCK) \
  X(ENOSYS) \
  X(ENOTEMPTY) \
  X(EILSEQ)
#endif

// type definitions for the specific machine

#ifdef __LP64__
typedef long mp_int_t; // must be pointer size
typedef unsigned long mp_uint_t; // must be pointer size
#elif defined ( __MINGW32__ ) && defined( _WIN64 )
#include <stdint.h>
typedef __int64 mp_int_t;
typedef unsigned __int64 mp_uint_t;
#else
// These are definitions for machines where sizeof(int) == sizeof(void*),
// regardless for actual size.
typedef int mp_int_t; // must be pointer size
typedef unsigned int mp_uint_t; // must be pointer size
#endif

// Cannot include <sys/types.h>, as it may lead to symbol name clashes
#if _FILE_OFFSET_BITS == 64 && !defined(__LP64__)
typedef long long mp_off_t;
#else
typedef long mp_off_t;
#endif

#define MP_PLAT_PRINT_STRN(str, len) (void)0

#ifndef MP_NOINLINE
#define MP_NOINLINE __attribute__((noinline))
#endif

// We need to provide a declaration/definition of alloca()
#ifdef __FreeBSD__
#include <stdlib.h>
#elif defined( _WIN32 )
#include <malloc.h>
#else
#include <alloca.h>
#endif

#include <stdint.h>
