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
  char temp[10] , deci[15];
  memset(temp , 0x0 , sizeof(temp));

  ser_add.sin_family = AF_INET;
  ser_add.sin_port = htons(atoi(buf[2]));
  ser_add.sin_addr.s_addr = inet_addr(buf[1]);

  int sock_desc, cli_desc ,length,deci_num,octal_num=0,i=1;
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
      cli_desc = (accept(sock_desc, (struct sockaddr*) &cli_add, &cli_len));
      if(cli_desc < 0){
          perror("Error in Client Socket\n");
          exit(1);
      }
      recv(cli_desc , deci ,sizeof(deci) , 0);
      deci_num = atoi(deci);
      printf("The decimal number received is-%d\n",deci_num);
      
      while (deci_num != 0)
      {
        octal_num += (deci_num % 8) * i;
        deci_num /= 8;
        i *= 10;
      }

      sprintf(temp,"%d",octal_num);
      send(cli_desc , temp , strlen(temp)+1, 0 );

     
      close(cli_desc);
  }
}
