CFLAGS = -Wall -W
EXECS = client server

all: client server

client: client.c definitions.h $(OBJ)
	gcc $(CFLAGS) client.c -o client

server: server.c definitions.h $(OBJ)
	gcc $(CFLAGS) server.c -o server

clean:
	rm $(EXECS)
