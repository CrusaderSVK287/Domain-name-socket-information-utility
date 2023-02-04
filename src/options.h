/*
 * Module contains both declarations for options related and
 * error message related functions, macros etc..
 */

#ifndef OPTIONS_H
#define OPTIONS_H

/* We are bitshifing because this enum is used in bitmasking */
enum error_level {
        ERR_INFO        = (1 << 0),
        ERR_WARNING     = (1 << 1),
        ERR_DEBUG       = (1 << 2),
        ERR_FATAL       = (1 << 3),
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

typedef struct options {
        int ipv4;
        int ipv6;
        int ipvall;

        int tcp;
        int udp;
        int ip;
        int tpall;

        int stream;
        int dgram;
        int raw;
        int stall;

        int compact;
} options_t;

/**
 * @brief Function parses command line arguments
 * 
 * @param argc 
 * @param argv 
 * @return 0 if successful, -1 if not 
 */
int parse_arguments(int argc, char **argv, options_t *opts);

#endif /* OPTIONS_H */
