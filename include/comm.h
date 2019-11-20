#include <poll.h>
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
};

struct comm_t* comm_init(const char* server_addr, const char* server_port);
void comm_destroy(struct comm_t* com);
int comm_write(struct comm_t* self, uint8_t* buf, size_t len);
int comm_read(struct comm_t* self, uint8_t* buf, size_t buf_size, time_t timeout);



