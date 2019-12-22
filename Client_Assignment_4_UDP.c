#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<netinet/in.h>
int main(int count,char *buf[]){
  if(count < 4){
        printf("Enter proper IP and Port Number");
        exit(1);
}
struct sockaddr_in cli_add,ser_add;
  int cli_desc,sock_desc,len = sizeof(cli_add);
  char temp[20];
  memset(temp , 0x0 ,sizeof(temp));

  ser_add.sin_family = AF_INET;
  ser_add.sin_port = htons(atoi(buf[2]));
  ser_add.sin_addr.s_addr = inet_addr(buf[1]);

  sock_desc = socket(AF_INET , SOCK_DGRAM , 0);
  if(sock_desc < 0){
      perror("Unable to Create Socket");
      exit(1);
  }

 if(connect(sock_desc , (struct sockaddr*) &ser_add, sizeof(ser_add)) < 0){
      perror("Connection Failed");
      exit(1);
  }

 sendto(sock_desc , buf[3] , strlen(buf[3])+1,MSG_CONFIRM,(struct sockaddr*)&ser_add,sizeof(ser_add));
 recvfrom(sock_desc,temp,sizeof(temp),MSG_WAITALL,(struct sockaddr*)&ser_add,&len);
 printf("The received reverse string is %s",temp);
 printf("\nsuccessful\n");


}

