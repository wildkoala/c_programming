#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX	1024
#define PORT	4567
#define BUFFER	200

// I didn't initialize the IP address.
// Must do that in order to connect!!

int main(int argc, char **argv){
    int my_sock = 0;
    int server_resp = 0;
    int val_read, success;
    struct sockaddr_in serv_addr;
    int addr_len = sizeof(serv_addr);
    const char my_string[100] = "CLIENT: Hey! This worked!"; // making this a buffer allow us to send the entire message. If you make it a pointer to a string, spaces will terminate the message.
    int my_string_size = sizeof(my_string);
    char response_buff[BUFFER];
    
    // initializing my sockaddr_in
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
     
    
    memset(response_buff,0,BUFFER);

    // create my socket
    printf("Creating socket...\n");
    my_sock = socket(AF_INET, SOCK_STREAM, 0);

    // connect to the server
    printf("Attempting to connect to server...\n");
    server_resp = connect(my_sock, (struct sockaddr*)&serv_addr, addr_len);

    if(server_resp<0){
	    printf("ERROR! Could not connect...\n");
	    exit(-1);
    }

    // send data, get response, print it out
    success = send(my_sock, &my_string, my_string_size, 0);
    val_read = read(my_sock, response_buff, BUFFER );
    printf("%s\n", response_buff);
    return 0;
}
