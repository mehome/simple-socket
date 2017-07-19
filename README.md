# simple-socket
Linux下的用C简单的对tcp和udp这两种socket操作进行的封装，方便使用

## interface

```c

int tcp_open(void);
int tcp_bind(int socket, int ip, int port);
int tcp_listen(int socket, int backlog);
int tcp_accept(int socket);
int tcp_connect(int socket, int ip, int port);
int tcp_send(int socket, char *data, int len);
int tcp_recv(int socket, char *buf, int len);
int tcp_reuse_address(int socket);
int tcp_block(int socket);
int tcp_nonblock(int socket);
int tcp_state(int socket);
int tcp_close(int socket);


```

## server example

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

## client example

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
