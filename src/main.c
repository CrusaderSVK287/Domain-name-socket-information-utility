#include "dn_info_util.h"
#include "options.h"
#include <stdio.h>

int main(int argc, char **argv)
{
        options_t opts = { 0 };
        
        if (parse_arguments(argc, argv, &opts) < 0)
                return 0;

        get_domain_name_info(argc, argv, &opts);
        return 0;
}
