#include <arpa/inet.h>
#include "inet_address.h"

const char* inet_get_ipstring(struct sockaddr_in *address)
{
	if( address )
	{
		return inet_ntoa( address->sin_addr );
	}
	return "0.0.0.0";
}
int inet_set_ipstring(struct sockaddr_in *address, const char *ip)
{
	if( address && ip )
	{
		inet_aton(ip, &address->sin_addr);
		return address->sin_addr.s_addr;
	}
	return -1;
}

int inet_get_ip(struct sockaddr_in *address)
{
	if( address )
	{
		return address->sin_addr.s_addr;
	}
	return -1;
}
int inet_set_ip(struct sockaddr_in *address, int ip)
{
	if( address )
	{
		address->sin_addr.s_addr = ip;
		return 0;
	}
	return -1;
}

int inet_get_family(struct sockaddr_in *address)
{
	if( address )
	{
		return address->sin_family;
	}
	return -1;
}
int inet_set_family(struct sockaddr_in *address, int family)
{
	if( address )
	{
		address->sin_family = family;
		return 0;
	}
	return -1;
}

int inet_get_port(struct sockaddr_in *address)
{
	if( address )
	{
		return ntohs(address->sin_port);
	}
	return -1;
}
int inet_set_port(struct sockaddr_in *address, int port)
{
	if( address )
	{
		address->sin_port = htons((short)port);
		return 0;
	}
	return -1;
}
