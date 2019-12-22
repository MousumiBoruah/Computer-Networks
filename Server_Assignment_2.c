#include<stdio.h>
#include<netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int count,char *buf[]){
  pid_t PID;
  if(count < 3){
        printf("Enter proper IP address and Port Number");
  }
  struct sockaddr_in ser_add;
  //int cli_len = sizeof(cli_add);
  char temp[25] , name[100];
  memset(temp , 0x0 , sizeof(temp));

  ser_add.sin_family = AF_INET;
  ser_add.sin_port = htons(atoi(buf[2]));
  ser_add.sin_addr.s_addr = inet_addr(buf[1]);

  int sock_desc ,length;
  if((sock_desc = socket(AF_INET,SOCK_STREAM,0)) < 0){
      perror("SOCKET ERROR");
      exit(1);
  }
  if(bind(sock_desc, (struct sockaddr*) &ser_add, sizeof(ser_add)) < 0){
      perror("Unable to Bind");
      exit(1);
  }
  if(listen(sock_desc , 2) < 0){
      perror("Unable to Listen");
      exit(1);
  }
  while(1){
      int cli_desc;
      struct sockaddr_in cli_add;
      printf("Waiting for the client to form connectivity\n");
      int cli_len = sizeof(cli_add);
      cli_desc = accept(sock_desc, (struct sockaddr*) &cli_add, &cli_len);
      if(cli_desc < 0){
         perror("Client Socket Error");
        exit(1);
        }
      PID = fork();
      if(PID == 0){
         close(sock_desc);
        recv(cli_desc , name ,sizeof(name) , 0);
        char rev[30];
        int i;
         for(i = 0;i < strlen(name);i++){
           rev[i] = name[strlen(name) -i-1];
        }
         rev[i] = '\0';
        printf("the reversed string is %s\n",rev);
        send(cli_desc,rev,strlen(rev)+1,0);
        close(cli_desc);
        exit(0);
     }
     else{
        close(cli_desc);
     }
  }

}

