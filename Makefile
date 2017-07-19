
all:
	make client
	make server

client: inet_address.c tcp_socket.c test-tcp-client.c
	gcc $+ -o $@

server: inet_address.c tcp_socket.c test-tcp-server.c
	gcc $+ -o $@

clean:
	@rm -rfv client
	@rm -rfv server 
