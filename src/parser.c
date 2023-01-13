#include "parser.h"
#include "options.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int get_domain_name(char *result, const char *input, size_t res_len)
{
        if (!result || !input)
                return -1;

        e_debug("Parsing %s\n", input);

        memset(result, 0x00, res_len);
        char *slashes = strstr(input, "//");
        long off = (slashes != NULL) ? ((long)slashes - (long)input + 2) : (0);

        char tmp = 0;
        int i = 0;
        for (i = 0; i < res_len; i++) {
                tmp = input[off + i];
                if (tmp == '/' || tmp == ':' || tmp == 0)
                        break;

                result[i] = tmp;
        }

        if (i == res_len) {
                e_warning("Domain name was not fully parsed due to short buffer\n", NULL);
        }

        e_debug("parsed %s of %d lenght\n", result, i);
        return 0;
}
