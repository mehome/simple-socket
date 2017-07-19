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
