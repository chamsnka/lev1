// server code:

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int cnt=0;

int main(int argc,char* argv[])
{
	//variable declarition
	int sockfd,newsockfd,portno,n;
	struct sockaddr_in server_addr,client_addr;
	char buf[1024];



	socklen_t addr_size;

	pid_t child_pid;


	//check for appropriate no. of command line input

	if(argc<2)
	{
		printf("provide required command line...\n");
		exit(1);
	}

	portno=atoi(argv[1]);

	//created the socket
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	//check if socket is created properly
	if(sockfd<0)
	{
		printf("error in opening socket\n");
		exit(1);
	}

	printf("server socket is created\n");

	memset(&server_addr,'\0',sizeof(server_addr));

	//build the structure of server address
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(portno);

	//bind the socket to the address and port no specified in structure

	if(bind(sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr))<0)
	{
		printf("Error in binding address\n");
	}

	//listen to any incoming client

	listen(sockfd,10);
	addr_size=sizeof(client_addr);


	while(1)
	{


		newsockfd=accept(sockfd,(struct sockaddr *)&client_addr,&addr_size);

		cnt++;
		//	printf("cnt is %d\n",cnt);
	
		//check if the client socket is created properly

		if(newsockfd<0)
		{
			printf("Error in accepting in request\n");
			exit(1);
		}

		printf("connection accepted from %s\t\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));


		if((child_pid=fork())==0)
		{
			printf("PID=%d\n",getpid());

			//		close(sockfd);
			while(1)
			{


				// clear buffer
				bzero(buf,sizeof(buf));

				//now read some data from the client
				read(newsockfd,buf,sizeof(buf));
				if(n<0)
				{
					printf("error in reading\n");
					exit(1);
				}


				//conversion lower case to upper case when reciving from client
				for(int i=0;buf[i]!='\0';i++)
				{
					if (buf[i] >= 'a' && buf[i] <= 'z')
					{
						buf[i]-=32;
					}
					else if(buf[i] >= 'A' && buf[i] <= 'Z')
					{
						buf[i]+=32;
					}
				}

				printf("from client %d:%s \t to client:",cnt,buf);


				bzero(buf,sizeof(buf));

				//now write some data to the client

				//	fgets(buf,1024,stdin);
				int n=0;
				while((buf[n++]=getchar())!='\n');
				write(newsockfd,buf,sizeof(buf));


			/*
				printf("enter a number from 1 to %d which client you want to reply\n", cnt);
				int num;

				scanf("%d", &num);

				switch(num)

				{
					case 1: printf("write on client 1\n");
						write(newsockfd, buf, sizeof(buf));
						printf("newSockfd %d", newsockfd);
						break;
					case 2:printf("Write on clinet 2\n");
					       write(newsockfd, buf, sizeof(buf));
					       printf("newSockfd %d", newsockfd);
					       break;
					case 3:printf("write on client 3\n");
					       write(newsockfd, buf, sizeof(buf));
					       printf("newSockfd %d", newsockfd);
					       break;
					default:printf("Invalid case\n");
				}

			*/


			}
		}

	}
	// close the files
	close(newsockfd);
	close(sockfd);
	return 0;

}


