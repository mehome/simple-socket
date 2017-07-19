# simple-socket
Linux下的用C简单的对tcp和udp这两种socket操作进行的封装，方便使用

```c
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

```
