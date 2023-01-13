#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

/**
 * @brief Function parses given input, be it domain name or a link,
 *        and parses domain name out of it
 *
 * @param result result array
 * @param input input array
 * @param res_len lenght of result array
 * @return 0 on success, -1 on error
 */
int get_domain_name(char *result, const char *input, size_t res_len);

#endif /* PARSER_H */
