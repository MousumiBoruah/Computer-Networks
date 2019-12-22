#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
 
#define MAX_CLIENT 2
 
void check_msg(char* received_msg){
    int i,k=0,check_parity=0,j=0,flag=0,count=0;
    for(i=(pow(2,k) - 1);i<12; i =(pow(2,k) - 1)) {
            j = i;
            while(j < 12) {
                check_parity = check_parity ^ (int)(received_msg[j] - '0');
                j++;
                flag++;
                if(flag == i + 1) {
                    j += i + 1;
                    flag=0;
                }
            }
            if(check_parity == 1){
                count += i+1;
            }
            check_parity = 0;
            k++;
         
    }
    if(received_msg[count-1] == '1'){
        received_msg[count-1] = '0';
    }
    else{
        received_msg[count-1] = '1';
    }
    printf("Corrected Message: %s\n", received_msg);
}
int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Few arguments -- <IP> <Port>\n");
        exit(1);
    }
    struct sockaddr_in client_addr, server_addr;
    int client_socket, server_socket, client_len, len;
    char string_buf[20];    
    // Inserting the server socket Data structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
 
    // creating a server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0) {
        perror("Socket cannot be created: ");
        exit(1);
    }
     
    // Binding of the socket to the port.
    if(bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Binding Error: ");
        exit(1);
    }
    // Listening for incoming functions
    if(listen(server_socket, MAX_CLIENT) < 0) {
        perror("Listening Error: ");
        exit(1);
    }
     
    while(1) {
        printf("Waiting For the Client to send Message\n");
        client_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_len);
        memset(string_buf, 0x0, sizeof(string_buf));
        recv(client_socket, string_buf, sizeof(string_buf), 0);
        printf("Received String: %s\n", string_buf);
        check_msg(string_buf);
        close(client_socket);   
    }
}