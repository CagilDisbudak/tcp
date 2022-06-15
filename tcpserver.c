#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MYPORT 3490 // the port users will be connecting to
#define BACKLOG 10 // how many pending connections queue will hold
int main() {
int sockfd, new_fd;
char isim[100];
struct sockaddr_in my_addr; // my address information
struct sockaddr_in their_addr; // connector's address information
int sin_size;
int yes = 1;
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
perror("socket");
exit(1);
}
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
my_addr.sin_family = AF_INET; // Internet Address Family (IP)
my_addr.sin_port = htons(MYPORT); // short, network byte order
my_addr.sin_addr.s_addr = INADDR_ANY;
memset(&(my_addr.sin_zero), '\0', 8);
if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
perror("bind");
exit(1);
}
if (listen(sockfd, BACKLOG) == -1) {
perror("listen");
exit(1);
}
sin_size = sizeof(struct sockaddr_in);
if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&sin_size)) == -1) {
perror("accept");
exit(1);
}
if (send(new_fd, "What is your name?\n", 20, 0) == -1) {
perror("send");
close(new_fd);
exit(0);
}
recv(new_fd,isim,100,0);
if (send(new_fd, "Hello" , 14, 0) == -1) {
perror("send");
exit(0);
}

sleep(1);

if (send(new_fd, isim, 15, 0) == -1) {
perror("send");
close(new_fd);
exit(0);
}
return 0;
}
