#include "comm.h"


struct msg_elem
{
    struct list_elem elem;
    uint8_t buf [MAVLINK_MAX_PACKET_LEN];
    size_t len;
};


static int init_connection(struct comm_t* com, const char* server_addr, const char* server_port);

static struct msg_elem* request_elem(struct comm_t* self);
static void return_elem (struct comm_t* self, struct msg_elem* msg);
static void free_elem (struct comm_t* self);

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

    ret = connect(com->client_sock, &com->client_addr, client_len);
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
    }
    list_init (&self->elem_buffer);

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

static struct msg_elem* request_elem (struct comm_t* self)
{
    struct msg_elem* msg = NULL;
    if (list_empty (&self->elem_buffer))
    {
        msg = malloc (sizeof (struct msg_elem));
        msg->len = 0;
        return msg;
    }
    return list_entry (list_pop_front(&self->elem_buffer), struct msg_elem, elem);
}

static void return_elem (struct comm_t* self, struct msg_elem* msg)
{
    memset (msg->buf, 0x00, MAVLINK_MAX_PACKET_LEN);
    msg->len = 0;
    list_push_front (&self->elem_buffer, &msg->elem);    
}


int comm_append_write (struct comm_t* self, uint8_t* buf, size_t len)
{
    struct msg_elem* msg = request_elem (self);
    memcpy (&msg->buf, buf, len);
    msg->len = len;

    list_push_back (&self->write_queue, &msg->elem);    
    return 0;
}




