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

/**
 * @brief Convert af number to string representation
 * 
 * @param af family type returned in ai_family
 * @return const char* 
 */
const char *get_address_family(int af);

/**
 * @brief Convert p number to string representation
 * 
 * @param p protocol type returned in ai_protocol
 * @return const char* 
 */
const char *get_protocol(int p);

/**
 * @brief Convert st number to string representation
 * 
 * @param st socktype returned in ai_socktype
 * @return const char* 
 */
const char *get_socktype(int st);

#endif /* PARSER_H */
