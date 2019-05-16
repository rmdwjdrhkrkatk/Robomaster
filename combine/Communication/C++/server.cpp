/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define port 12345

int sockfd, newsockfd, portno;
socklen_t clilen;
float buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n;



void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void get_socket_data() {
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);

    if (newsockfd < 0) error("ERROR on accept");
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("x: %f y: %f d: %f\n",buffer[0], buffer[1], buffer[2]);
    // n = write(newsockfd,"I got your message",18);
}

void init_socket_server() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
}


int main()
{

    init_socket_server();
    while(1) {



        get_socket_data();



    }

    close(newsockfd);
    close(sockfd);

}