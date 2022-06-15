#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<time.h>
void genTok(char* msg, char*** arg);

main()
{
	int sockid;
	int bindid, pid,fd	;
	struct sockaddr_in myaddr;
	struct sockaddr_in client;
	int newsockid;
	int clientlen;

	char msg[100];
	int recvid;
	int port_id = 6000;


	sockid = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char*)&myaddr, sizeof(struct sockaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);//"192.168.23.39");
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
		//system(msg);
		
		if((pid=fork())<0)
			printf("Error\n");
		if(pid==0) {
			char** arg;
			genTok(msg,&arg);
			time_t ltime;
			ltime=time(NULL);
			char filename[130]="";
			strcat(filename,"output.");
			strcat(filename,arg[0]);
			strcat(filename,".");
			strcat(filename,asctime(localtime(&ltime)));
			strcat(filename,".txt");

			int fd=creat(filename,O_RDWR);
			close(1);
			dup(fd);
			close(fd);
			//execvp(arg[0],arg);
			system(arg[]
		}
		else
			close(newsockid);
	}

	return 0;
}

void genTok(char* msg, char*** arg)
{
	(*arg)=(char**)malloc(10*sizeof(char*));
	int i;
	char* ptr;
	(*arg)[0]=(char*)malloc(10);
	ptr=strtok(msg," ");
	strcpy((*arg)[0],ptr);
	//printf("%s\n",(*arg)[0]);
	for(i=1;;i++) {
		ptr=strtok(NULL," ");
	
		if(ptr==NULL) {
			//printf("**");
			(*arg)[i]=NULL;
			break;
		}
		(*arg)[i]=(char*)malloc(10);

		strcpy((*arg)[i],ptr);
		//printf("%s\n",(*arg)[i]);

	}
}

