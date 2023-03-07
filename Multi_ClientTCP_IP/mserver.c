# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

# define SERVER_ADDR "127.0.0.1"

void Communicate(int sock,int clno)
{     printf("SERVER Chat Terminal\n");
     printf("Use \"bye\" for exit\n\n"); 
   char buf[1024];
   int quit;
	int n;
	while(1)
	{    
	      	bzero(buf,1024);
	        n=recv(sock,buf,sizeof(buf),0);
	          quit = strcmp(buf,"bye");
	          if(quit==10)
	  	  {quit=0;}
                if(quit == 0)
                { 
		printf("Client %d disconnected\n",clno);
		sleep(30);
		return;
                }
               else
         	{
	       	printf("\nClient %d: %s",clno,buf);
		bzero(buf,1024);
		printf("Server Reply: ");
		fgets(buf,sizeof(buf)-1,stdin);
		send(sock,buf,strlen(buf),0);
         	}
      }
	}	



void main(int argc,char *argv[])
{

	int serverSocfd,port,newsocketd,size;
	struct sockaddr_in server,client;
	pid_t childpid;
        int clientno=0;

	serverSocfd = socket(AF_INET,SOCK_STREAM,0);/*IPV4,TCP*/
	if(serverSocfd<0)
	{
		perror("Socket Error");
		exit(0);
	}


	memset(&server, '\0', sizeof(server));
	port = atoi(argv[1]);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	server.sin_port = port;

	
        int  n = bind(serverSocfd,(struct sockaddr*)&server,sizeof(server));
	if(n<0)
{
	perror("The destination port and Ip binding unsuccesfull");
                exit(0);
}
       printf("Binded to port no %d\n",port);


	listen(serverSocfd,30);
	printf("..............Listening..............\n");
	while(1)
	{
		size = sizeof(client);
		newsocketd = accept(serverSocfd,(struct sockaddr*)&client,&size);
	        printf("Connection accepted from: %s at port: %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		clientno = clientno+1;
		childpid=fork();
		if(childpid==0)
		{ 
			close(serverSocfd);
	         Communicate(newsocketd,clientno);
		break;
		
		}

	}
      close(newsocketd);
}

