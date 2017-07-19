
all:
	make clien
	make server

clien: inet_address.c tcp_socket.c test-tcp-client.c
	gcc $+ -o $@

server: inet_address.c tcp_socket.c test-tcp-server.c
	gcc $+ -o $@

clean:
	@rm -rfv clien
	@rm -rfv server 
