/*
 * Module contains both declarations for options related and
 * error message related functions, macros etc..
 */

#ifndef OPTIONS_H
#define OPTIONS_H

enum error_level {
        ERR_INFO        = 0b00000001,
        ERR_WARNING     = 0b00000010,
        ERR_DEBUG       = 0b00000100,
        ERR_FATAL       = 0b00001000,
};

#ifdef _err
#undef _err
#endif
/* DO NOT CALL DIRECTLY, USE APPROPRIATE MACRO FOR ERROR LOGGING */
void _err(int level, const char *msg, ...);

/* macros used to print debug/info messages, must have at least
   one variable argument (put NULL for no argument) */
#define e_info(msg, ...)        (_err)(ERR_INFO, msg, __VA_ARGS__)
#define e_warning(msg, ...)     (_err)(ERR_WARNING, msg, __VA_ARGS__)
#define e_debug(msg, ...)       (_err)(ERR_DEBUG, msg, __VA_ARGS__)
#define e_fatal_error(msg, ...) (_err)(ERR_WARNING | ERR_FATAL, msg, __VA_ARGS__)

#define _err(...) do_not_call_directly_use_e__macros

#endif /* OPTIONS_H */
