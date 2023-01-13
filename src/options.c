#include "options.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define print_err(msg) fprintf(stderr, "%s\n", msg)

#ifdef _err
#undef _err
#endif

void _err(int level, const char *msg, ...)
{
        if (level < 0 || !msg) {
                print_err("Wrong error level");
                exit(1);
        }

        va_list args;
        va_start(args, msg);

#ifndef NDEBUG
        if (level == ERR_DEBUG) {
                vfprintf(stdout, msg, args);
                goto out;
        }
#endif /* NDEBUG */

        if (level == ERR_INFO) {
                vfprintf(stdout, msg, args);
                goto out;
        }

        if (level & ERR_WARNING)
                vfprintf(stderr, msg, args);

        if (level & ERR_FATAL)
                exit(1);

out:
        va_end(args);
}

#ifndef _err
#define _err(...) do_not_call_directly_use_e__macros
#endif
