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
