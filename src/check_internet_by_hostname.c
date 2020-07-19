/*#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <netdb.h> 
#include <resolv.h>
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
*/
/*int main()
  {
  int ret = Check_internet_by_hostname("visiontek.co.in");
  if (ret == 0)
  {
  puts("Connection Avliable");
  }
  else
  {
  puts("Data connection not Avliable");
  }
  }*/
#include<header.h>
int Check_internet_by_hostname(char *host,char *ip)
{
        struct in_addr **addr_list;
	int sockfd;  
	struct hostent *he;
	struct sockaddr_in their_addr;
	int i;
	res_init();

	if ((he=gethostbyname(host)) == NULL) {  
		herror("gethostbyname");
		return -1;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return -1;
	}

	their_addr.sin_family = AF_INET;      /* host byte order */
	their_addr.sin_port = htons(80);    /* short, network byte order */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

	if (connect(sockfd, (struct sockaddr *)&their_addr, \
				sizeof(struct sockaddr)) == -1) {
		perror("connect");
		close(sockfd);
		return -1;
	}
	addr_list = (struct in_addr **) he->h_addr_list;

        for(i = 0; addr_list[i] != NULL; i++)
                strcpy(ip , inet_ntoa(*addr_list[i]) );

	close(sockfd);
	return 0;

}
