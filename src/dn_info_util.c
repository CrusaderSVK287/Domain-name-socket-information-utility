#include "dn_info_util.h"
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
                if (argv[0] == '-')
                        continue;
                //parse dn
                //call contact dns
        }
}
