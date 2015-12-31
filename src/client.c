#include "../include/definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

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
    laddr.sin_port = htons(CPORT);
    laddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // create address of remote socket
    struct sockaddr_in raddr = { 0 };
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(SPORT);
    raddr.sin_addr.s_addr = htonl(INADDR_ANY);

    char buf[BUF_SIZE] = { 0 };

    // bind socket to address
    if (bind(lsock, (struct sockaddr *)&laddr, ADDRLEN) < 0) {
        perror("Could not bind client socket");
        exit(1);
    }

    // tcp connect to server
    if (connect(lsock, (struct sockaddr *)&raddr, ADDRLEN) < 0) {
        perror("Client failed to connect to server");
        printf("Make sure to run the server first!\n");
        exit(1);
    }

    // send data
    strcpy(buf, "Hello server!");
    printf("Sending to server: '%s'\n", buf);
    write(lsock, (void *)buf, BUF_SIZE);
    //send(lsock, (void *)buf, BUF_SIZE, 0);
    clear_buf((void *)buf, BUF_SIZE);

    // receive response
    read(lsock, (void *)buf, BUF_SIZE);
    //recv(lsock, (void *)buf, BUF_SIZE, 0);
    printf("Receving from server: '%s'\n", buf);
    clear_buf((void *)buf, BUF_SIZE);

    close(lsock);

    return 0;
}
