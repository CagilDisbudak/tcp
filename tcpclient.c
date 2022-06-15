#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 3490
#define MAXDATASIZE 100 // max number of bytes we can get at once
int main() {
char IP[16];
int sockfd, numbytes;
char buf[MAXDATASIZE];
char muf[MAXDATASIZE];
char isim[100];
struct sockaddr_in server; // connector's address information
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
perror("socket");
exit(1);
}
server.sin_family = AF_INET; // Internet Address Family (IP)
server.sin_port = htons(PORT); // short, network byte order
printf("\n\n\nEnter IP address of the Server\n");
scanf("%s", IP);
server.sin_addr.s_addr = inet_addr(IP);
memset(&(server.sin_zero), '\0', 8);
if (connect(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
perror("connect");
exit(1);
}
if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1) {
perror("recv");
exit(1);
}
buf[numbytes] = '\0';
printf("Received: %s", buf);



scanf("%s", isim);
if (send(sockfd, isim, 30, 0) == -1) {
perror("send");
close(sockfd);
exit(0);
}

if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1) {
perror("recv");
exit(1);
}
buf[numbytes] = '\0';
printf("Received: %s", buf);



if ((numbytes = recv(sockfd, muf, MAXDATASIZE - 1, 0)) == -1) {
perror("recv");
exit(1);
}
muf[numbytes] = '\0';
printf(" %s", muf);


close(sockfd);
return 0;
}
