// Write a Client-Server based socket program in C to transfer a text file from client to the server. The prototypes to run the client and servers are as below.
// $./server <IP Address> <Port No>
// $./client <Server's IP address> <Server's Port No> <File Name>
#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>

int main(int count,char *buf[]){

  if(count < 3){
        printf("Enter proper IP address and Port Number");
  }
  struct sockaddr_in ser_add,cli_add;
  int cli_len = sizeof(cli_add);
  char temp[25] , name[15];
  memset(temp , 0x0 , sizeof(temp));

  ser_add.sin_family = AF_INET;
  ser_add.sin_port = htons(atoi(buf[2]));
  ser_add.sin_addr.s_addr = inet_addr(buf[1]);

  int sock_desc, cli_desc ,length;
  if((sock_desc = socket(AF_INET,SOCK_STREAM,0)) < 0){
      perror("SOCKET ERROR");
      exit(1);
  }
  if(bind(sock_desc,(struct sockaddr*) &ser_add, sizeof(ser_add)) < 0){
      perror("Unable to Bind");
      exit(1);
  }
  if(listen(sock_desc , 2) < 0){
      perror("Unable to Listen");
      exit(1);
  }
  while(1){
      printf("Waiting for the client to form connectivity\n");
      cli_len = sizeof(cli_add);
      cli_desc = accept(sock_desc, (struct sockaddr*) &cli_add, &cli_len);
      if(cli_desc < 0){
          perror("Error in Client Socket\n");
          exit(1);
      }
      recv(cli_desc , name ,sizeof(name) , 0);
      FILE *tar = fopen(name,"w");
      while((length = recv(cli_desc ,temp ,10,0))){
          fputs(temp,tar);
          memset(temp,0x0,sizeof(temp));
      }
      fclose(tar);
      close(cli_desc);
  }
}
