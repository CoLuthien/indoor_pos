#include "comm.h"
#include <time.h>


struct msg_elem
{
    struct list_elem elem;
    uint8_t buf [MAVLINK_MAX_PACKET_LEN];
    size_t len;
};


static int init_connection(struct comm_t* com, const char* server_addr, const char* server_port);

static struct msg_elem* request_elem(struct comm_t* self);
static void return_elem (struct comm_t* self, struct msg_elem* msg);
static void free_elem (struct comm_t* self, struct msg_elem* msg);

static inline int init_socket(struct comm_t* com, const char* i_addr, const char* port)
{
    com->client_sock = socket(AF_INET, SOCK_STREAM, 0);
    com->client_addr.sin_family = AF_INET;
    com->client_addr.sin_addr.s_addr = inet_addr(i_addr);
    com->client_addr.sin_port =htons(atoi(port));

    return com->client_sock;
}

static int init_connection(struct comm_t* com, const char* server_addr, const char* server_port)
{
    int ret = -1;
    int fd = -1;
    size_t client_len = sizeof(com->client_addr);

    fd = init_socket(com, server_addr, server_port);
    if (fd < 0)
    {
        return fd;// fail to open socket
    }

    ret = connect(com->client_sock, (struct sockaddr*)&com->client_addr, client_len);
    com->pfd.fd = com->client_sock;
    com->pfd.events = POLLIN;
    return ret;
}

struct comm_t* comm_init(const char* server_addr, const char* server_port)
{
    struct comm_t* self = malloc(sizeof(struct comm_t));
    if(init_connection(self, server_addr, server_port) < 0)
    {
        comm_destroy(self);
        printf("comm init fail\n");
        return NULL;
    }
    printf("%d", self->client_addr.sin_port);
    list_init (&self->elem_buffer);
    list_init (&self->read_queue);
    list_init (&self->write_queue);

    printf("comm init success\n");

    return self;
}

void comm_destroy(struct comm_t* com)
{
    close(com->client_sock);
    free(com);
    com = NULL;
}

int comm_write(struct comm_t* self, uint8_t* buf, size_t len)
{
    return write(self->client_sock, buf, len);
}

/*
    ret > 0 => read success
    ret == 0 => notthing arrive
    ret < 0 => read or poll is fail.
*/
int comm_read(struct comm_t* self, uint8_t* buf, size_t buf_size, time_t timeout)
{
    int poll_ret = poll(&self->pfd, 1, timeout);
    if (poll_ret <= 0)
    {
        return -1; // recovery process need
    }

    if (self->pfd.revents & POLLIN)
    {
        return read(self->pfd.fd, buf, buf_size);        
    }

    return poll_ret;
}

int comm_do_write (struct comm_t* self, int timeout)
{
    //for now we don't care about timeout. process just 1 request per call
    if (list_empty (&self->write_queue))
    {
        return -1;
    }
    int nread = -1, len = 0;
    short int old_evt = self->pfd.events;

    self->pfd.events = POLLOUT | POLLHUP;
    struct msg_elem* msg = list_entry (list_pop_front (&self->write_queue), struct msg_elem, elem);
    
    nread = poll (&self->pfd, 1, timeout);
    if (nread <= 0)
    {
        goto fail;
    }

    if (self->pfd.revents & POLLOUT)
    {
        goto success;
    }

    fail:
        list_push_back (&self->write_queue, &msg->elem);
        return -1;

    success:
        len = write (self->pfd.fd, msg->buf, msg->len);
       
        return_elem (self, msg);
        return len;
}

int comm_do_read (struct comm_t* self, int timeout)
{
    struct msg_elem* msg = request_elem (self);
    if (NULL == msg)
    {
        return -1;
    }

    int nread = -1, len = 0;
    short int old_evt = self->pfd.events;
    self->pfd.events = POLLIN;
    
    nread = poll (&self->pfd, 1, timeout);
    if (nread <= 0)
    {
        goto fail;
    }

    if (self->pfd.events & POLLIN)
    {
        goto success;
    }

    fail:
        return_elem (self, msg);
        return -1;

    success:
        len = read (self->pfd.fd, msg->buf, MAVLINK_MAX_PACKET_LEN);
        msg->len = len;
        list_push_back (&self->read_queue, &msg->elem);
 
        return 0;
}

static struct msg_elem* request_elem (struct comm_t* self)
{
    struct msg_elem* msg = NULL;
    if (list_empty (&self->elem_buffer))
    {
        msg = malloc (sizeof (struct msg_elem));
        msg->len = 0;
        return msg;
    }

    msg = list_entry (list_pop_front(&self->elem_buffer), struct msg_elem, elem);
    return msg;
}

static void return_elem (struct comm_t* self, struct msg_elem* msg)
{
    memset (msg->buf, 0x00, MAVLINK_MAX_PACKET_LEN);
    msg->len = 0;
    list_push_front (&self->elem_buffer, &msg->elem);    
}

static void free_elem (struct comm_t* self, struct msg_elem* msg)
{
    free(msg);
}


int comm_append_write (struct comm_t* self, uint8_t* buf, size_t len)
{
    struct msg_elem* msg = request_elem (self);
    memcpy (&msg->buf, buf, len);
    msg->len = len;
    list_push_back (&self->write_queue, &msg->elem); 
    return 0;
}

int comm_try_read (struct comm_t* self, uint8_t* buf, size_t len)
{
    if (list_empty (&self->read_queue))
        return -1;
        
    struct msg_elem* msg = NULL;
    int ret = 0;
    struct list_elem* e = list_pop_front (&self->read_queue);
    msg = list_entry (e, struct msg_elem, elem);
    ret = msg->len;
    memcpy (buf, msg->buf, msg->len);

    return_elem(self, msg);

    return ret;
}




