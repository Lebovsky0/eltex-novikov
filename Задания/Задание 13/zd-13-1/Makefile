CC = gcc
CFLAGS = -Wall

all: posix sysv

# POSIX
posix: posix-server posix-client

posix-server: zd-13-1-posix-server.c
	$(CC) $(CFLAGS) zd-13-1-posix-server.c -o zd-13-1-posix-server -lrt

posix-client: zd-13-1-posix-client.c
	$(CC) $(CFLAGS) zd-13-1-posix-client.c -o zd-13-1-posix-client -lrt

# SYSTEM V
sysv: sysv-server sysv-client

sysv-server: zd-13-1-sysv-server.c
	$(CC) $(CFLAGS) zd-13-1-sysv-server.c -o zd-13-1-sysv-server

sysv-client: zd-13-1-sysv-client.c
	$(CC) $(CFLAGS) zd-13-1-sysv-client.c -o zd-13-1-sysv-client

clean:
	rm -f zd-13-1-posix-server zd-13-1-posix-client zd-13-1-sysv-server zd-13-1-sysv-client

