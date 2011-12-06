/*
    Public Domain License
*/
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>

#ifndef SOCK_PATH
    #define SOCK_PATH "/var/run/mon/snmptrap"
#endif

int main(int argc, char *argv[]) {
    
    int sockfd;
    struct sockaddr_un sa;
    char buf[4096];
    size_t bytes_read;

    sockfd = socket(PF_UNIX,SOCK_DGRAM,0);
    if (-1 == sockfd) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
    memset(&sa, 0, sizeof sa);
    sa.sun_family  = AF_UNIX;
    strncpy(sa.sun_path, SOCK_PATH, sizeof(sa.sun_path) - 1);
    if (connect(sockfd, (struct sockaddr *) &sa, strlen(sa.sun_path) + sizeof(sa.sun_family)) < 0)
        perror("cannot connect to socket");
    while(!feof(stdin)) {
        bytes_read = fread(buf, sizeof(buf), 1, stdin);
        write(sockfd,buf,strlen(buf));
    }
    exit(EXIT_SUCCESS);
}
