//Lab Assignment#5: Implementation of a data link layer channel with error correction
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/socket.h>

void Hamming_Code(char* input_msg, char* transmitted_msg) {
    int i,k=0,parity=0,j=0,flag=0;
    for(i=(pow(2,k) - 1);i<12; i =(pow(2,k) - 1)) {
            j = i;
            while(j < 12) {
                parity = parity ^ (int)(transmitted_msg[j] - '0');
                j++;
                flag++;
                if(flag == i + 1) {
                    j += i + 1;
                    flag=0;
                }
            }
            //printf("%d ", parity);
            transmitted_msg[i] = parity + '0';
            parity = 0;
            k++;
        
    }
    printf("\nThe message after hamming code is generated is: %s\n", transmitted_msg);

}

void introduce_error(char* transmitted_msg, float probability){
    int *left_part, *right_part, left_size, right_size,j=0, random_number, error;
    left_size = (int)(probability * 10);
    right_size = 10 - left_size;
    srand(time(0)); // seeds the random num generator 
    random_number = rand() % 10;
    //printf("%d\n", random_number);
    if(random_number >= (left_size-1)){
        error = 0;
        printf("No Error\n");
    }
    else{
        error = 1;
        printf("Yes\n");
    }
    if(error == 1){
        random_number = rand() % 12;
        printf("Position: %d\n", random_number);
        if(transmitted_msg[random_number] == '1'){
            transmitted_msg[random_number] = '0';
        }
        else{
            transmitted_msg[random_number] = '1';
        }
    }
    printf("The transmitted message to the server is %s\n", transmitted_msg);

}

int main(int argc, char const *argv[]) {
    char input_msg[9], transmitted_msg[13];
    //strcpy(input_msg, argv[1]);
    printf("Please Enter the message\n");
    scanf("%s",input_msg);
    input_msg[8] = '\0';
    int k=0,i,j=0;
    float probability;
    //preprocessing step
    for(i=0; i<12; ++i) {
        if(i == (pow(2,k) - 1)) {
            transmitted_msg[i] = '0';
            k++;
        }
        else {
            transmitted_msg[i] = input_msg[j++];
        }
    }
    transmitted_msg[i] = '\0';
    Hamming_Code(input_msg, transmitted_msg);
    printf("Please Enter the probability\n");
    scanf("%f",&probability);
    introduce_error(transmitted_msg, probability);
    struct sockaddr_in server_addr;
    int client_socket;
    // Inserting the server socket Data structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    // creating a server socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket < 0) {
        perror("Socket cannot be created: ");
        exit(1);
    }

    if(connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0 ) {
        perror("Connection Failed: ");
        exit(1);
    }
    send(client_socket, transmitted_msg, strlen(transmitted_msg), 0);
    //printf("--Sending--DONE--\n");
    return 0;
}