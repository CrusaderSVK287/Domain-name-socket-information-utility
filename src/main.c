#include "dn_info_util.h"
#include <stdio.h>

int main(int argc, char **argv)
{
        if (argc < 2)
                printf("Usage: %s domain.name-1 domain.name-2 ...\n", argv[0]);

        get_domain_name_info(argc, argv);
        return 0;
}
