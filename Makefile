CFLAGS = -Wall -W
EXECS = client server

all: client server

client: src/client.c include/definitions.h
	gcc $(CFLAGS) src/client.c -o client

server: src/server.c include/definitions.h
	gcc $(CFLAGS) src/server.c -o server

clean:
	rm $(EXECS)
