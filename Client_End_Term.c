#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>

int main(int count,char *buf[]){
	if(count < 4){
		perror("Enter Proper IP address and Port Number\n");
		exit(0);
	}
  struct sockaddr_in cli_add,ser_add;
  int cli_desc,sock_desc,num;
  char temp[20];
  memset(temp , 0x0 ,sizeof(temp));
  // printf("Please Enter the Decimal Number\n");
  // scanf("%d",&num);

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

  send(sock_desc , buf[3] , strlen(buf[3]), 0 );
  recv(sock_desc,temp,sizeof(temp),0);
  printf("\nThe Decimal Number sent is %s",buf[3]);
  printf("\nThe Octal Number received is %s\n",temp);



}