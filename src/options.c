#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "options.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>

#define print_err(msg) fprintf(stderr, msg)

#ifdef _err
#undef _err
#endif

static void print_help();

void _err(int level, const char *msg, ...)
{
        if (level < 0 || !msg) {
                print_err("Wrong error level\n");
                exit(1);
        }

        va_list args;
        va_start(args, msg);

#ifndef NDEBUG
        if (level == ERR_DEBUG) {
                print_err("DEBUG: ");
                vfprintf(stdout, msg, args);
                goto out;
        }
#endif /* NDEBUG */

        if (level == ERR_INFO) {
                vfprintf(stdout, msg, args);
                goto out;
        }

        if (level & ERR_WARNING) {
                print_err("Warning: ");
                vfprintf(stderr, msg, args);
        }

        if (level & ERR_FATAL) {
                print_err("FATAL ERROR\n");
                exit(1);
        }

out:
        va_end(args);
}

#ifndef _err
#define _err(...) do_not_call_directly_use_e__macros
#endif


#define usage e_warning("*** Error parsing arguments, use '%s --help'"\
                                " to see list of available options\n",\
                                argv[0])

int parse_arguments(int argc, char **argv, options_t *opts)
{
        if (!argv || !opts)
                return -1;

        if (argc < 2) {
                usage;
                return -1;
        }

        /* These indicate all sockets of the family should be printed */
        opts->ipvall = 1;
        opts->tpall = 1;
        opts->stall = 1;

        static struct option long_options[] = {
                /* IP protocol version */
                {"ipv4",        no_argument,    0, '4'},  /* print ipv4 */
                {"ipv6",        no_argument,    0, '6'},  /* print ipv6 */

                /* Transport protocol */
                {"tcp",         no_argument,    0, 't'},  /* print tcp protocol */
                {"udp",         no_argument,    0, 'u'},  /* print udp protocol */

                /* Socket type */
                {"stream",      no_argument,    0, 's'},  /* print stream sockets */
                {"dgram",       no_argument,    0, 'd'},  /* print datagram sockets */
                {"raw",         no_argument,    0, 'r'},  /* print raw sockets */

                {"version",     no_argument,    0, 'v'},  /* version */
                {"help",        no_argument,    0, 'h'},  /* help */
                {0,             0,              0,  0 }
        };

        int opt_index = 0;
        int c = 0;

        while ((c = getopt_long(argc, argv, "46tusdr", long_options,
                &opt_index)) != -1) {
                switch (c)
                {
                case '4': opts->ipv4 = 1;
                        opts->ipvall = 0;
                        break;
                case '6': opts->ipv6 = 1;
                        opts->ipvall = 0;
                        break;
                
                case 't': opts->tcp = 1;
                        opts->tpall = 0;
                        break;
                case 'u': opts->udp = 1;
                        opts->tpall = 0;
                        break;

                case 's': opts->stream = 1;
                        opts->stall = 0;
                        break;
                case 'd': opts->dgram = 1;
                        opts->stall = 0;
                        break;
                case 'r': opts->raw = 1;
                        opts->stall = 0;
                        break;

                case 'h':
                        print_help();
                        return -1;
                case 'v':
                        printf("Domain name socket information utility\n\n"
                                "\tVersion 1.0\n\n"
                                "Visit github page here\n"
                                "https://github.com/CrusaderSVK287/Domain-name-information-utility\n");
                        return -1;

                case '?':
                default:
                        usage;
                        return -1;
                }
        }

        return 0;
}

static void print_help()
{
        printf("Help page not yet implemented\n");
}
