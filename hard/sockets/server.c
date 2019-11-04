#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h> // for all the socket stuff
#include <stdlib.h> //for exit

#define PORT 4567
#define MAX  3
#define BUFFER	200


int main(int argc, char **argv){
    int new_socket;
    int val_read;
    int opt = 1;
    struct sockaddr_in address;
    
    printf("Creating server...\n");
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    int addr_len = sizeof(address);
    char buffer[BUFFER];
    memset(buffer,0,BUFFER);
    
    const char *hello = "SERVER HERE";

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT); //set the port
    address.sin_addr.s_addr = INADDR_ANY;

    // Check that we got a good file descriptor.
    if (server_fd < 0){
        perror("Socket failed...");
        exit(EXIT_FAILURE);
    }

    // consider putting some error handling here to see if it's bound
    // dont think that sizeof will work. Need to point to member within sockaddr
    printf("Binding to port...\n");
    bind(server_fd, (struct sockaddr *)&address,addr_len); // tried this, compiles

    // consider putting some error handling to see if it never listens
    printf("Listening...\n");
    listen(server_fd, MAX);

    // okay now make the new socket with an accepted client
    // need pointer to address, not the address object itself. just gonna cast
    // same for the length.
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addr_len);
    printf("Client connected\n");

    val_read = read(new_socket, buffer, BUFFER);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("SERVER HERE was sent to the client.\n");
    return 0;
}
