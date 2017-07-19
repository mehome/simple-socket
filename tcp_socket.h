#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

/*
 enum
{
  TCP_ESTABLISHED	= 1,
  TCP_SYN_SENT		= 2,
  TCP_SYN_RECV		= 3,
  TCP_FIN_WAIT1		= 4,
  TCP_FIN_WAIT2		= 5,
  TCP_TIME_WAIT		= 6,
  TCP_CLOSE			= 7,
  TCP_CLOSE_WAIT	= 8,
  TCP_LAST_ACK		= 9,
  TCP_LISTEN		= 10,
  TCP_CLOSING		= 11 
};
 */

typedef enum
{
	tcpo_reuse= 1,
	tcpo_block= 2,
	tcpo_unblock= 3,
	tcpo_state = 4,
}tcp_option_t;

int tcp_open(void);
int tcp_bind(int socket, int ip, int port);
int tcp_listen(int socket, int backlog);
int tcp_accept(int socket);
int tcp_connect(int socket, int ip, int port);
int tcp_send(int socket, char *data, int len);
int tcp_recv(int socket, char *buf, int len);
int tcp_setoption(int socket, tcp_option_t tcpo);
int tcp_getoption(int socket, tcp_option_t tcpo);
int tcp_state(int socket);
int tcp_close(int socket);

#endif//__TCP_SOCKET_H__
