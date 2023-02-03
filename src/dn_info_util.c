#define _POSIX_C_SOURCE 200112L

#include "dn_info_util.h"
#include "options.h"
#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define HTTP_PORT "80"

/* Function contacts dns server to obtain information */
static int dn_info(const char *dn, options_t *opts);
/* Function prints all information from addrinfo */
static int print_addrinfo(const struct addrinfo *a, options_t *opts);
/* Function determines whether socket should be printed or not.
 * Returns 1 if yes, 0 if not */
static int print_socket(const struct addrinfo *a, options_t *opts);

void get_domain_name_info(int argc, char **argv, options_t *opts)
{
        if (!argv || !opts)
                return;

        char buff[BUFSIZ];
        memset(buff, 0x00, BUFSIZ);

        for (int i = 1; i < argc; i++) {
                if (argv[i][0] == '-')
                        continue;

                if (get_domain_name(buff, argv[i], BUFSIZ) < 0) {
                        e_info("There was an error with parsing domain "
                               "name from %s, skipping\n", argv[i]);
                        continue;
                }

                if (dn_info(buff, opts) < 0) {
                        e_warning("Failed to obtain domain name information\n", NULL);
                        continue;
                }
        }
}

static int dn_info(const char *dn, options_t *opts)
{
        if (!dn || !opts)
                return -1;

        int ret = 0;
        struct addrinfo *res = NULL;
        /* Since res is being changed, keep the reference to free */
        struct addrinfo *tmp = NULL;
        struct addrinfo hints = {0};

        hints.ai_family         = AF_UNSPEC;    /* Support both ipv4 and 6 addresses */
        hints.ai_socktype       = 0;            /* Any socket type */
        hints.ai_flags          = 0;
        hints.ai_protocol       = IPPROTO_IP;   /* Any protocol */

        if ((ret = getaddrinfo(dn, HTTP_PORT, &hints, &res)) < 0) {
                e_warning("Failed to obtain domain name info due to: %s\n", gai_strerror(ret));
                if (ret == EAI_SYSTEM)
                        e_warning(strerror(ret), NULL);

                return -1;
        }

        tmp = res;
        while (res != NULL) {
                if (print_addrinfo(res, opts) < 0)
                        e_warning("Could not print address info\n", NULL);

                res = res->ai_next;
        }

        freeaddrinfo(tmp);

        return 0;
}

static int print_addrinfo(const struct addrinfo *a, options_t *opts)
{
        if (!a || !opts)
                return -1;

        if (!print_socket(a, opts))
                return 0;

        char addrbuf[BUFSIZ];
        memset(addrbuf, 0x00, BUFSIZ);

        /* Getting ipv4 or ipv6 address in a human-readable form */
        switch(a->ai_family) {
        case AF_INET:
                struct sockaddr_in *addr_in = (struct sockaddr_in *)a->ai_addr;
                inet_ntop(AF_INET, &(addr_in->sin_addr), addrbuf, BUFSIZ);
                break;
        case AF_INET6:
                struct sockaddr_in6 *addr_in6 = (struct sockaddr_in6 *)a->ai_addr;
                inet_ntop(AF_INET6, &(addr_in6->sin6_addr), addrbuf, BUFSIZ);
                break;
        default:
                break;
        }

        printf("address:              %s\n"
                "address family: %4d  %s\n"
                "protocol:       %4d  %s\n"
                "type:           %4d  %s\n"
                "\n",
                addrbuf,
                a->ai_family,   get_address_family(a->ai_family),
                a->ai_protocol, get_protocol(a->ai_protocol),
                a->ai_socktype, get_socktype(a->ai_socktype));

        return 0;
}

static int print_socket(const struct addrinfo *a, options_t *opts)
{
        if (!a || !opts)
                return 0;       /* do not print */

        /* IP protocol version check if dont print all */
        if (!opts->ipvall && (
                (a->ai_family == AF_INET && !opts->ipv4) ||
                (a->ai_family == AF_INET6 && !opts->ipv6)
        )) return 0;

        if (!opts->tpall && (
                (a->ai_protocol == IPPROTO_TCP && !opts->tcp) ||
                (a->ai_protocol == IPPROTO_UDP && !opts->udp)
        )) return 0;

        if (!opts->stall && (
                (a->ai_socktype == SOCK_STREAM && !opts->stream) ||
                (a->ai_socktype == SOCK_DGRAM && !opts->dgram) ||
                (a->ai_socktype == SOCK_RAW && !opts->raw)
        )) return 0;

        /* print socket */
        return 1;
}
