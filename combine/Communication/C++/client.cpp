#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define host_addr "localhost"
#define port 12345


float buffer[256];
int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void init_socket() {
    portno = port;

    server = gethostbyname(host_addr);


    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
}

void send_socket(float x, float y, float d) {

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");


    bzero(buffer,256);
    // fgets(buffer,255,stdin);

    ////////data here///////////
    buffer[0] = x;
    buffer[1] = y;
    buffer[2] = d;
    /////////////////////////////
    // n = write(sockfd,buffer,strlen(buffer));
    n = write(sockfd,buffer,255);
    if (n < 0) {
        error("ERROR writing to socket");
    }
    bzero(buffer,256);
    // n = read(sockfd,buffer,255);
    // if (n < 0) {
    // error("ERROR reading from socket");
    close(sockfd);
}

int main()
{
    init_socket();

    while(1) {
        send_socket(1.1, 2.5, 3.4);
    }
}