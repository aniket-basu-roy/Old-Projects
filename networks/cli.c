#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

main()
{
	int sockid;
	int connectid;
	struct sockaddr_in servaddr;
	struct sockaddr_in client;
	int newsockid;
	int clientlen;

	char msg[100];
	printf("Enter the command\n");
	gets(msg);
	int sendid;
	int port_id = 6000;


	sockid = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char*)&servaddr, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//"192.168.23.39");
	servaddr.sin_port = htons(port_id);
	connectid = connect(sockid, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in));

	if(connectid < 0)
		printf("error \n");


	sendid = sendto(sockid, msg, 100, 0, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in));
	if(sendid < 0)
		printf("error 2\n");



	return 0;
}
