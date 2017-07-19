
all:
	make tcpclient
	make tcpserver
	make udpclient
	make udpserver

tcpclient: inet_address.c tcp_socket.c test-tcp-client.c
	gcc $+ -o $@

tcpserver: inet_address.c tcp_socket.c test-tcp-server.c
	gcc $+ -o $@

udpclient: inet_address.c udp_socket.c test-udp-client.c
	gcc $+ -o $@

udpserver: inet_address.c udp_socket.c test-udp-server.c
	gcc $+ -o $@


clean:
	@rm -rfv *.o
	@rm -rfv *client
	@rm -rfv *server 
