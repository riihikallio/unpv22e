#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define ERR(msg) { perror(msg); exit(1); }
#define PORT 54321
#define HOST "128.214.9.98"

// Driver code
int main(void) {
	int sockfd;
	char *ptr = malloc(1024);
	struct sockaddr_in servaddr;
	
	// Filling server information
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
    if (inet_aton(HOST, &servaddr.sin_addr) == 0) ERR("invalid IP address");

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) ERR("socket creation failed");

    if(sendto(sockfd, ptr, 1024, 0, 
            (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) ERR("sendto failed");
    close(sockfd);

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) ERR("socket creation failed");

    // Connect the socket for 2b
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) ERR("connecting socket failed");

    if(send(sockfd, ptr, 1024, 0) < 0) ERR("send failed");
    close(sockfd);

    free(ptr);
	return 0;
}
