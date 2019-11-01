#include <stdio.h>
#include <sys/socket.h> // not sure if ill need permissions to  use this?
#include <netinet/in.h>
#include <unistd.h> // need this for read()
#include <string.h>
#include <arpa/inet.h>  //need for inet_pton, converting string to network address
#define PORT 4567

/*
I will have a simple client here that connects and receives a message
then sends "hello server" to the server.
*/

int main(int argc, char const *argv[]) {
    int sock = 0;
    int valread;
    struct sockaddr_in server_addr;
    char *hello_server = "Hello server\n";
    char buffer[1024] = {0};

    // printf(hello_server);

    // create the socket. (Address + port)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr); //pton vs aton?

    // Error checking, defing that were using TCP.
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }


    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }


    // write the stuff that is sent over the socket into the buffer
    // flush that buffer to standard input
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    // accept input from the user (for now, it's defined already)
    // send the users's input to the server
    send(sock, hello_server, strlen(hello_server), 0);
    printf("Hello message sent\n"); 
    return 0;
}
