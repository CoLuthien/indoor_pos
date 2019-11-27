#ifndef _COMM_H
#define _COMM_H

#include "list.h"
#include "mavlink.h"

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>


struct comm_t
{
    struct pollfd pfd;
    int client_sock; // file descriptor
    struct sockaddr_in client_addr;
    struct list write_queue;
    struct list read_queue;
    struct list elem_buffer;//private. 
};

struct comm_t* comm_init(const char* server_addr, const char* server_port);
void comm_destroy(struct comm_t* com);

int comm_write(struct comm_t* self, uint8_t* buf, size_t len);
int comm_read(struct comm_t* self, uint8_t* buf, size_t buf_size, time_t timeout);

int comm_do_write (struct comm_t* self, int timeout);
int comm_do_read (struct comm_t* self, int timeout);

int comm_append_write (struct comm_t* self, uint8_t* buf, size_t len);
int comm_try_read (struct comm_t* self, uint8_t* buf, size_t len);

#endif
