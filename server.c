#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h> //used in sin_family,sin_port,sin_addr
#include<arpa/inet.h> //the available the types in_port_t and type in_addr_t as defined

 


#define PORT 4455

 

int main()
{
    int sockfd;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    socklen_t addr_size;
    char buffer[1024];

 

    //socket - create an endpoint for communication
    sockfd=socket(PF_INET, SOCK_STREAM, 0);
    printf("[+]server socket created sucessfully\n");

 

    memset(&serverAddr,'\0',sizeof(serverAddr));

    serverAddr.sin_family=AF_INET;

    //htons is convert values between host and network byte order
    serverAddr.sin_port=htons(PORT);

 

    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //bind a name to a socket
    bind(sockfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("[+]bind to the port number %d\n",4455);

 

    //listen for connections on a socket
    listen(sockfd, 5);
    printf("[+]listening....\n");

 


    addr_size=sizeof(newAddr);

    //accept a connection on a socket
    newSocket=accept(sockfd,(struct sockaddr*)&newAddr,&addr_size);

    strcpy(buffer,"chandra\n");

 

    //send a message on a socket
    send(newSocket,buffer,strlen(buffer)+1,0);

 

    printf("[+]send the data to the client\n");
    printf("[+]closong the connection\n");

}   
