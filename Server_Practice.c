#include<stdio.h>
#include<netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>


int main(int argc,char *buf[]){
	if(argc < 3){
		printf("Enter proper arguments\n");
		exit(0);
	}

	struct sockaddr_in server_address,client_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(buf[2]));
	server_address.sin_addr.s_addr = inet_addr(buf[1]);

	int sock_desc,cli_desc;
	if((sock_desc = socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("socket error");
		exit(0);
	} 

	if(bind(sock_desc,(struct sockaddr*) &server_address,sizeof(server_address)) < 0){
		perror("biding error");
		exit(0);
	}

	if(listen(sock_desc,2) < 0){
		perror("linstening error");
		exit(0);
	}
	int cli_len;
	char name[10],rev[10];
	while(1){
		printf("Waiting\n");
		cli_len = sizeof(client_address);
		cli_desc = accept(sock_desc,(struct sockaddr*) &client_address,&cli_len);
		if(cli_desc  < 0){
			perror("äccepting error");
			exit(0);
		}

		recv(cli_desc,name,sizeof(name),0);
		int i;
         for(i = 0;i < strlen(name);i++){
           rev[i] = name[strlen(name) -i-1];
        }
         rev[i] = '\0';
         send(cli_desc,rev,strlen(rev)+1,0);
         close(cli_desc);
         exit(0);


	}
}