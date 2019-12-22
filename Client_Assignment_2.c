// Write a client-server based program using socket programming, where the client after making the connection to the server will send a STRING to the server, and the server will REVERSE the STRING and send the reversed string to the client as its reply. The client should display the reply received from the server. The server should be implemented as a concurrent server, so that multiple clients can connect to the server at the same time. The prototype for the client and server are as below.

// $ <Server> <IP address> <Port No>
// $ <Client> <IP address of server> <Port no of server> <String to be reversed>
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<netinet/in.h>
int main(int count,char *buf[]){
  if(count < 4){
        printf("Enter proper IP and Port Number");
        exit(1);
}
struct sockaddr_in cli_add,ser_add;
  int cli_desc,sock_desc;
  char temp[20];
  memset(temp , 0x0 ,sizeof(temp));

  ser_add.sin_family = AF_INET;
  ser_add.sin_port = htons(atoi(buf[2]));
  ser_add.sin_addr.s_addr = inet_addr(buf[1]);

  sock_desc = socket(AF_INET , SOCK_STREAM , 0);
  if(sock_desc < 0){
      perror("Unable to Create Socket");
      exit(1);
  }

 if(connect(sock_desc , (struct sockaddr*) &ser_add, sizeof(ser_add)) < 0){
      perror("Connection Failed");
      exit(1);
  }

 send(sock_desc , buf[3] , strlen(buf[3])+1 , 0 );
 recv(sock_desc,temp,sizeof(temp),0);
 printf("The received reverse string is %s",temp);
 printf("\nsuccessful\n");


}
