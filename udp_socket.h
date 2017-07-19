#ifndef __UDP_SOCKET_H__
#define __UDP_SOCKET_H__

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

#endif//__UDP_SOCKET_H__
