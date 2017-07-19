#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include "tcp_socket.h"
#include "inet_address.h"

int tcp_open(void)
{
	return socket(AF_INET, SOCK_STREAM, 0);
}
int tcp_bind(int socket, int ip, int port)
{
	struct sockaddr_in address;

	bzero(&address, sizeof(address));
	inet_set_family(&address, AF_INET);
	inet_set_ip(&address, ip);
	inet_set_port(&address, port);
	return bind(socket, (struct sockaddr*)&address, sizeof(address));
}
int tcp_listen(int socket, int backlog)
{
	return listen(socket, backlog);
}
int tcp_accept(int socket)
{
	struct sockaddr_in address;
	socklen_t socklen = sizeof(address);

	bzero(&address, sizeof(address));
	return accept(socket, (struct sockaddr*)&address, &socklen); 
}
int tcp_connect(int socket, int ip, int port)
{
	struct sockaddr_in address;

	bzero(&address, sizeof(address));
	inet_set_family(&address, AF_INET);
	inet_set_ip(&address, ip);
	inet_set_port(&address, port);
	return connect(socket, (struct sockaddr*)&address, sizeof(address));
}
int tcp_send(int socket, char *data, int len)
{
	if( data && len > 0 )
	{
		return send(socket, (const void*)data, (size_t)len, 0);
	}
	return -1;
}
int tcp_recv(int socket, char *buf, int len)
{
	if( buf && len > 0 )
	{
		return recv(socket, (void*)buf, (size_t)len, 0);
	}
	return -1;
}
int tcp_setoption(int socket, tcp_option_t tcpo)
{
	int value = 0;
	socklen_t len = sizeof(value);

	switch( tcpo )
	{
		case tcpo_reuse:
			value = 1;
			return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (void*)&value, len);
		case tcpo_block:
			value = fcntl(socket, F_GETFL);
			value = value & ~(O_NONBLOCK);
			return fcntl(socket, F_SETFL, value);
		case tcpo_unblock:
			value = fcntl(socket, F_GETFL);
			value = value | O_NONBLOCK;
			return fcntl(socket, F_SETFL, value);
	}
	return -1;
}
int tcp_getoption(int socket, tcp_option_t tcpo)
{
	return 0;
}
int tcp_state(int socket)
{
	socklen_t len;
	struct tcp_info info;

	len = sizeof(info);
	bzero(&info, len);
	if( getsockopt(socket, IPPROTO_TCP, TCP_INFO, &info, &len) )
	{
		return -1;
	}
	return info.tcpi_state;
}
int tcp_close(int socket)
{
	return close(socket);
}
