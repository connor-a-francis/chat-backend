#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>

#define PORT 3000


void getLocal(struct addrinfo*);
int makeSocket(struct addrinfo*);
void enableReuse(int);
void bindInitial(int, struct addrinfo*);
void listenInitial(int);

int main(int argc, char const* argv[]) {
    struct addrinfo *res;
    int sockfd;

    getLocal(res);
    sockfd = makeSocket(res);
    enableReuse(sockfd);
    bindInitial(sockfd, res);
    listenInitial(sockfd);
    freeaddrinfo(res);

}

void getLocal(struct addrinfo *res) {
    struct addrinfo hints;
    int status;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((status = getaddrinfo(NULL, "3000", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    freeaddrinfo(&hints);
}

int makeSocket(struct addrinfo *res) {
    int sockfd;
    if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        perror("socket initialization");
        exit(1);
    }
    return sockfd;
}

void enableReuse(int sockfd) {
    int yes = 1;
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
        perror("setsockopt");
        exit(1);
    }
}

void bindInitial(int sockfd, struct addrinfo *res) {
    if ((bind(sockfd, res->ai_addr, res->ai_addrlen)) == -1) {
        perror("socket binding");
        exit(1);
    }
}

void listenInitial(int sockfd) {
    if ((listen(sockfd, 20)) == -1) {
        perror("listening on socket");
        exit(1);
    }
}
