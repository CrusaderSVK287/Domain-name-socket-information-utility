#include "dn_info_util.h"
#include "options.h"
#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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
                //call contact dns
        }
}
