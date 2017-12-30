.PHONY:all
all:server client



server: server.c common.c
	gcc -o $@ $^


client: client.c common.c
	gcc -o $@ $^


.PHNOY:cl
cl:
	rm -rf client server

