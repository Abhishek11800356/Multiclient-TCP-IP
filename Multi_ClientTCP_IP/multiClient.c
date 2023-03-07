#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void Communicate(int sock)
{        printf("Client Chat Terminal\n");
	printf("Use \"bye\" to close the chat\n\n");
	char buf[1024];
	int n,quit,quit2;
	while(1)
	{       bzero(buf,1024); 
	        printf("Client: ");
                fgets(buf,sizeof(buf)-1,stdin);
                send(sock,buf,strlen(buf),0);	
		quit = strcmp(buf,"bye");
                  if(quit==10)
                  {quit=0;}
                if(quit == 0)
                {
                 char s[20];
                 strcpy(s,"Client left\n");
                send(sock,s,strlen(s),0);
		printf("...................Disconnected...................\n");
                close(sock);
                exit(1);
                }
		bzero(buf,1024);
                if(recv(sock,buf,sizeof(buf),0)<0)
		{
			printf("Receive Failed\n");
		}
		else
	        {
		printf("Server Reply: %s\n",buf); 
		}
	}

}

void main(int argc,char *argv[])
{

	int clientSofd,port,cnxt;
	struct sockaddr_in server;
	clientSofd = socket(AF_INET,SOCK_STREAM,0);
	if(clientSofd<0)
	{
		printf("Socket Error\n");
		exit(0);
	}
	port = atoi(argv[2]);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = port;

	cnxt = connect(clientSofd,(struct sockaddr*)&server,sizeof(server));
	if(cnxt<0)
	{
		printf("Connection Failed\n");
		exit(1);
	}
	printf("****************Connected with Server****************\n\n");
	Communicate(clientSofd);
}

