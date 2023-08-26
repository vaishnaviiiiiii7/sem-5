//connection based socket programming server side in C.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // Parse the port number from command line arguments
    int port = atoi(argv[1]);

    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(1);
    }

    // Bind the socket to the specified port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding");
        close(server_socket);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Error listening");
        close(server_socket);
        exit(1);
    }

    printf("Server is listening on port %d...\n", port);

    // Accept a client connection
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1) {
        perror("Error accepting client connection");
        close(server_socket);
        exit(1);
    }

    printf("Connection established with client.\n");

    // Exchange messages
    char message[1024];
    while (1) {
        // Receive a message from the client
        if (recv(client_socket, message, sizeof(message), 0) <= 0) {
            perror("Error receiving message");
            break;
        }
        printf("Client: %s\n", message);

        // Send a response
        printf("Server: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        // Check for the "close" message from the client
        if (strcmp(message, "close\n") == 0) {
            printf("Connection closed by client.\n");
            break;
        }
    }

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}

