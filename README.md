# simple-socket
Linux下的用C简单的对tcp和udp这两种socket操作进行的封装，方便使用

## tcp socket interface

```c


int tcp_open(void);
int tcp_bind(int socket, int ip, int port);
int tcp_listen(int socket, int backlog);
int tcp_accept(int socket);
int tcp_connect(int socket, int ip, int port);
int udp_connects(int socket, const char *ip, int port);
int tcp_send(int socket, char *data, int len);
int tcp_recv(int socket, char *buf, int len);
int tcp_reuse_address(int socket);
int tcp_block(int socket);
int tcp_nonblock(int socket);
int tcp_state(int socket);
int tcp_close(int socket);


```

## tcp server example

```c

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tcp_socket.h"


int main(int argc, char **argv)
{
	int lsock = -1;
	int wsock = -1;
	int lastime = time(0);

	lsock = tcp_open();
	tcp_reuse_address(lsock);
	tcp_bind(lsock, 0, 9999);
	tcp_listen(lsock, 1);
	wsock = tcp_accept(lsock);
	tcp_nonblock(wsock);

	while(wsock > 0)
	{
		char buf[32] = {0};

		bzero(buf, sizeof(buf));
		if( tcp_recv(wsock, buf, sizeof(buf)) > 0 )
		{
			buf[sizeof(buf)-1] = 0;
			printf("recv:%s\n", buf);
			tcp_send(wsock, buf, strlen(buf));
		}
		else
		{
			if( time(0) - lastime > 0 )
			{
				lastime = time(0);
				printf("wsock(%d).state=%d\n", wsock, tcp_state(wsock)); 
				if( tcp_state(wsock) > 1 )
				{
					break;
				}
			}
		}
		usleep(1000);
	}//while(wsock>0)
	tcp_close(wsock);
	tcp_close(lsock);

	return 0;
}


```

## tcp client example

```c

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tcp_socket.h"


int main(int argc, char **argv)
{
	int wsock = -1;
	int lastime = time(0);

	wsock = tcp_open();
	tcp_nonblock(wsock);
	tcp_connect(wsock, 0, 9999);

	while(wsock > 0)
	{
		char buf[32] = {0};

		bzero(buf, sizeof(buf));
		if( tcp_recv(wsock, buf, sizeof(buf)) > 0 )
		{
			buf[sizeof(buf)-1] = 0;
			printf("recv:%s\n", buf);
		}
		else
		{
			if( time(0) - lastime > 0 )
			{
				char *p = "hello there, anyone hear me?";
				lastime = time(0);
				tcp_send(wsock, p, strlen(p));
				if( tcp_state(wsock) != 1 )
				{
					break;
				}
			}
		}
		usleep(1000);
	}//while(while>0)
	tcp_close(wsock);

	return 0;
}


```

## udp interface

```c


int udp_open(void);
int udp_bind(int socket, int ip, int port);
int udp_listen(int socket, int backlog);
int udp_connect(int socket, int ip, int port);
int udp_connects(int socket, const char *ip, int port);
int udp_send(int socket, char *data, int len);
int udp_recv(int socket, char *buf, int len);
int udp_sendto(int socket, char *data, int len, int ip, int port);
int udp_recvfrom(int socket, char *buf, int len, int *ip, int *port);
int udp_reuse_address(int socket);
int udp_block(int socket);
int udp_nonblock(int socket);
int udp_close(int socket);



```

## udp server example

```c


#include <stdio.h>
#include <string.h>
#include <time.h>
#include "udp_socket.h"


int main(int argc, char **argv)
{
	int lsock = -1;
	int lastime = time(0);

	lsock = udp_open();
	udp_reuse_address(lsock);
	udp_bind(lsock, 0, 9999);
	udp_listen(lsock, 1);
	udp_nonblock(lsock);

	while(lsock > 0)
	{
		int ip = 0;
		int port = 0;
		char buf[32] = {0};

		bzero(buf, sizeof(buf));
		if( udp_recvfrom(lsock, buf, sizeof(buf), &ip, &port) > 0 )
		{
			buf[sizeof(buf)-1] = 0;
			printf("recv:%s\n", buf);
			udp_sendto(lsock, buf, strlen(buf), ip, port);
		}
		else
		{
			if( time(0) - lastime > 0 )
			{
				lastime = time(0);
				printf("lsock(%d)\n", lsock); 
			}
		}
		usleep(1000);
	}//while(lsock>0)
	udp_close(lsock);

	return 0;
}


```

## udp client example


```c


#include <stdio.h>
#include <string.h>
#include <time.h>
#include "udp_socket.h"


int main(int argc, char **argv)
{
	int wsock = -1;
	int lastime = time(0);

	wsock = udp_open();
	udp_nonblock(wsock);
	udp_connect(wsock, 0, 9999);

	while(wsock > 0)
	{
		char buf[32] = {0};

		bzero(buf, sizeof(buf));
		if( udp_recv(wsock, buf, sizeof(buf)) > 0 )
		{
			buf[sizeof(buf)-1] = 0;
			printf("recv:%s\n", buf);
		}
		else
		{
			if( time(0) - lastime > 0 )
			{
				char data[32];

				lastime = time(0);
				snprintf(data, sizeof(data), "client(%d)\n", getpid());
				udp_send(wsock, data, strlen(data));
			}
		}
		usleep(1000);
	}//while(while>0)
	udp_close(wsock);

	return 0;
}


```
