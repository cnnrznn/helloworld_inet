#ifndef __DEFS_H
#define __DEFS_H

#include <string.h>
#include <netinet/in.h>

#define BUF_SIZE 256

#define CPORT 1024
#define SPORT 1025

const socklen_t ADDRLEN = sizeof(struct sockaddr_in);

void clear_buf(void *buf, size_t size) {
    memset(buf, 0, size);
}

#endif /* __DEFS_H */
