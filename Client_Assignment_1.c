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
  if(count < 4){
        printf("Enter proper IP and Port Number");
        exit(1);
}

  struct sockaddr_in cli_add,ser_add;
  int cli_desc,sock_desc;
  FILE *f_target = fopen(buf[1],"r");
  char temp[20];
  memset(temp , 0x0 ,sizeof(temp));

  ser_add.sin_family = AF_INET;
  ser_add.sin_port = htons(atoi(buf[3]));
  ser_add.sin_addr.s_addr = inet_addr(buf[2]);

  sock_desc = socket(AF_INET , SOCK_STREAM , 0);
  if(sock_desc < 0){
      perror("Unable to Create Socket");
      exit(1);
  }

 if(connect(sock_desc , (struct sockaddr*) &ser_add, sizeof(ser_add)) < 0){
      perror("Connection Failed");
      exit(1);
  }

 send(sock_desc , buf[1] , strlen(buf[1]), 0 );
 while(fgets(temp , 20 , f_target)){
        send(sock_desc , temp ,strlen(temp),0);
        memset(temp , 0x0 , sizeof(temp));
 }

  fclose(f_target);
  printf("successful\n");


}
