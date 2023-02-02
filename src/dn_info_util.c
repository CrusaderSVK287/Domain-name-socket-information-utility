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
static int dn_info(const char *dn);
/* Function prints all information from addrinfo */
static int print_addrinfo(const struct addrinfo *a);

void get_domain_name_info(int argc, char **argv)
{
        if (!argv)
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

                if (dn_info(buff) < 0) {
                        e_warning("Failed to obtain domain name information\n", NULL);
                        continue;
                }
        }
}

static int dn_info(const char *dn)
{
        if (!dn)
                return -1;

        int ret = 0;
        struct addrinfo *res = NULL;
        /* Since res is being changed, keep the reference to free */
        struct addrinfo *tmp = NULL;
        struct addrinfo hints = {0};

        hints.ai_family         = AF_UNSPEC;    /* Support both ipv4 and 6 addresses */
        hints.ai_socktype       = 0;            /* Any socket type */
        hints.ai_flags          = AI_CANONNAME;
        hints.ai_protocol       = IPPROTO_IP;   /* Any protocol */

        if ((ret = getaddrinfo(dn, HTTP_PORT, &hints, &res)) < 0) {
                e_warning("Failed to obtain domain name info due to: %s\n", gai_strerror(ret));
                if (ret == EAI_SYSTEM)
                        e_warning(strerror(ret), NULL);

                return -1;
        }

        tmp = res;
        while (res != NULL) {
                if (print_addrinfo(res) < 0)
                        e_warning("Could not print address info\n", NULL);

                res = res->ai_next;
        }

        freeaddrinfo(tmp);

        return 0;
}

static int print_addrinfo(const struct addrinfo *a)
{
        if (!a)
                return -1;

        char addrbuf[BUFSIZ];
        memset(addrbuf, 0x00, BUFSIZ);

        if (!inet_ntop(a->ai_family, a->ai_addr, addrbuf, BUFSIZ))
                e_warning("Failed to convert address from ntop", NULL);

        printf("address: %s\n"
                "address family: %s\n"
                "protocol %d\n"
                "type %d\n"
                "\n",
                addrbuf,
                get_address_family(a->ai_family),
                a->ai_protocol,
                a->ai_socktype);

        return 0;
}
