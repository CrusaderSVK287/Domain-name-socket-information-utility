#include "dn_info_util.h"
#include "options.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
        options_t opts = { 0 };
        /* Make all flags 0 */
        memset(&opts, 0x00, sizeof(opts));
        
        if (parse_arguments(argc, argv, &opts) < 0)
                return 0;

        get_domain_name_info(argc, argv, &opts);
        return 0;
}
