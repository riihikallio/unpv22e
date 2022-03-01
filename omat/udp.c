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
	char *ptr;
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) ERR("socket creation failed");

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
    if (inet_aton(HOST, &servaddr.sin_addr) == 0) ERR("invalid IP address");
	
    int i;
	for (i=1; i < INT_MAX; i*=2) {
        printf("%dKiB\n", i);
        ptr = malloc(i*1024);
        if(sendto(sockfd, ptr, i*1024, 0, 
            (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
                perror("sendto failed");
                free(ptr);
                break;
            }
        free(ptr);
    }
	for ( ; i>0; i--) {
        printf("%dKiB\n", i);
        ptr = malloc(i*1024);
        if(sendto(sockfd, ptr, i*1024, 0, 
            (const struct sockaddr *)&servaddr, sizeof(servaddr)) >= 0) {
                free(ptr);
                break;
            }
        free(ptr);
    }
    printf("%dKiB passes\n", i);
	
	close(sockfd);
	return 0;
}
