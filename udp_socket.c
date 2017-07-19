#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/udp.h>
#include "udp_socket.h"
#include "inet_address.h"

int udp_open(void)
{
	return socket(AF_INET, SOCK_DGRAM, 0);
}
int udp_bind(int socket, int ip, int port)
{
	struct sockaddr_in address;

	bzero(&address, sizeof(address));
	inet_set_family(&address, AF_INET);
	inet_set_ip(&address, ip);
	inet_set_port(&address, port);
	return bind(socket, (struct sockaddr*)&address, sizeof(address));
}
int udp_listen(int socket, int backlog)
{
	return listen(socket, backlog);
}
int udp_connect(int socket, int ip, int port)
{
	struct sockaddr_in address;

	bzero(&address, sizeof(address));
	inet_set_family(&address, AF_INET);
	inet_set_ip(&address, ip);
	inet_set_port(&address, port);
	return connect(socket, (struct sockaddr*)&address, sizeof(address));
}
int udp_connects(int socket, const char *ip, int port)
{
	if( ip )
	{
		struct sockaddr_in address;

		inet_set_ipstring(&address, ip);
		return udp_connect(socket, inet_get_ip(&address), port);
	}
	return -1;
}
int udp_send(int socket, char *data, int len)
{
	if( data && len > 0 )
	{
		return send(socket, (const void*)data, (size_t)len, 0);
	}
	return -1;
}
int udp_recv(int socket, char *buf, int len)
{
	if( buf && len > 0 )
	{
		return recv(socket, (void*)buf, (size_t)len, 0);
	}
	return -1;
}
int udp_sendto(int socket, char *data, int len, int ip, int port)
{
	if( data && len > 0 )
	{
		struct sockaddr_in address;
		socklen_t slen  = sizeof(address);

		bzero(&address, sizeof(address));
		inet_set_family(&address, AF_INET);
		inet_set_ip(&address, ip);
		inet_set_port(&address, port);
		return sendto(socket, data, len, 0, (struct sockaddr*)&address, slen);
	}
	return -1;
}
int udp_recvfrom(int socket, char *buf, int len, int *ip, int *port)
{
	if( buf && len > 0 && ip && port )
	{
		int ret = 0;
		struct sockaddr_in address;
		socklen_t slen = sizeof(address);

		bzero(&address, sizeof(address));
		ret = recvfrom(socket, buf, len, 0, (struct sockaddr*)&address, &slen);
		if( ret > 0 )
		{
			*ip = inet_get_ip(&address);
			*port = inet_get_port(&address);
			return ret;
		}
		return ret;
	}
	return -1;
}
int udp_reuse_address(int socket)
{
	int value = 1;
	socklen_t len = sizeof(value);

	return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (void*)&value, len);
}
int udp_block(int socket)
{
	int value = 0;

	value = fcntl(socket, F_GETFL);
	value = value & ~(O_NONBLOCK);
	return fcntl(socket, F_SETFL, value);
}

int udp_nonblock(int socket)
{
	int value = 0;

	value = fcntl(socket, F_GETFL);
	value = value | O_NONBLOCK;
	return fcntl(socket, F_SETFL, value);
}
int udp_close(int socket)
{
	return close(socket);
}
