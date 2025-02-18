#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>

#define PORT 3000


void getLocal(struct addrinfo**);
int makeSocket(struct addrinfo*);
void enableReuse(int);
void bindInitial(int, struct addrinfo*);
void listenInitial(int);
int acceptNewConns(int, sockaddr_storage, int);

int main(int argc, char const* argv[]) {
    struct sockaddr_storage their_addr;
    struct addrinfo *res;
    int sockfd, new_fd;
    int buffer_size = 1000;
    char *buffer = (char*)malloc(buffer_size * sizeof(char));
    memset(buffer, 0, buffer_size);

    getLocal(&res);
    sockfd = makeSocket(res);
    enableReuse(sockfd);
    bindInitial(sockfd, res);
    listenInitial(sockfd);
    new_fd = acceptNewConns(sockfd, their_addr, new_fd);
    int req_len = recv(new_fd, buffer, buffer_size, 0);

    if (req_len == -1) {
        perror("listening on socket");
        exit(1);
    }

    if (req_len == 0) {
        std::cout << "Connection closed!";
    } else {
        send(new_fd, buffer, req_len, 0);
        std::cout << buffer;
    }
    
    
    freeaddrinfo(res);

}

void getLocal(struct addrinfo **res) {
    struct addrinfo hints;
    int status;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     

    if ((status = getaddrinfo(NULL, "3000", &hints, res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
}

int makeSocket(struct addrinfo *res) {
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
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

int acceptNewConns(int sockfd, struct sockaddr_storage their_addr, int new_fd) {
    socklen_t addr_size;
    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_fd == -1) {
        perror("accepting new connections");
        exit(1);
    }
    return new_fd;
}
