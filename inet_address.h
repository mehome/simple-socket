#ifndef __INET_ADDRESS_H__
#define __INET_ADDRESS_H__
#include <netinet/in.h>

const char* inet_get_ipstring(struct sockaddr_in *address);
int inet_set_ipstring(struct sockaddr_in *address, const char *ip);

int inet_get_ip(struct sockaddr_in *address);
int inet_set_ip(struct sockaddr_in *address, int ip);

int inet_get_family(struct sockaddr_in *address);
int inet_set_family(struct sockaddr_in *address, int family);

int inet_get_port(struct sockaddr_in *address);
int inet_set_port(struct sockaddr_in *address, int port);

#endif//__INET_ADDRESS_H__
