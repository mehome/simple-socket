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
