#ifndef DN_INFO_UTIL_H
#define DN_INFO_UTIL_H

#include "options.h"

/**
 * @brief Function prints information about all domain names specified in argv
 *
 * @param argc
 * @param argv
 */
void get_domain_name_info(int argc, char **argv, options_t *opts);

#endif /* DN_INFO_UTIL_H */
