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
