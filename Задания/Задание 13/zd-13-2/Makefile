CC = gcc
CFLAGS = -Wall -pthread

all: server client

server: zd-13-2-server.c
	$(CC) $(CFLAGS) zd-13-2-server.c -o zd-13-2-server

client: zd-13-2-client.c
	$(CC) $(CFLAGS) zd-13-2-client.c -o zd-13-2-client -lncurses

clean:
	rm -f zd-13-2-server zd-13-2-client

