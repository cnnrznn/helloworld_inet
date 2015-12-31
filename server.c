#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BACKLOG 5

int main()
{
    int lsock; // local socket fd
    if ((lsock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Could not allocate client socket");
        exit(1);
    }

    // create address of local socket
    struct sockaddr_in laddr = { 0 };
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(SPORT);
    laddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // create address of remote socket
    struct sockaddr_in raddr = { 0 };
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(CPORT);
    raddr.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t raddrlen;

    char buf[BUF_SIZE] = { 0 };

    // bind socket to address
    if (bind(lsock, (struct sockaddr *)&laddr, ADDRLEN) < 0) {
        perror("Could not bind server socket");
        exit(1);
    }

    // listen on lsock
    if (listen(lsock, BACKLOG) < 0) {
        perror("Error listening on server port");
        exit(1);
    }

    // accept connection
    int rsock;
    if ((rsock = accept(lsock, (struct sockaddr *)&raddr, &raddrlen)) < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    // receive message
    //read(rsock, (void *)buf, BUF_SIZE);
    recv(rsock, (void *)buf, BUF_SIZE, 0);
    printf("Receving from client: '%s'\n", buf);
    clear_buf((void *)buf, BUF_SIZE);

    // send response
    strcpy(buf, "I got your message!");
    //write(rsock, buf, BUF_SIZE);
    send(rsock, buf, BUF_SIZE, 0);
    clear_buf((void *)buf, BUF_SIZE);

    close(lsock);
    close(rsock);

    return 0;
}
