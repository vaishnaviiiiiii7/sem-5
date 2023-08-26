//conection based socket programming client file in C.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(1);
    }

    // Parse server IP and port from command line arguments
    char *server_ip = argv[1];
    int server_port = atoi(argv[2]);

    // Create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating client socket");
        exit(1);
    }

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &(server_address.sin_addr));

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        close(client_socket);
        exit(1);
    }

    printf("Connected to server at %s:%d\n", server_ip, server_port);

    char message[1024];

    // Exchange messages
    while (1) {
        printf("Client: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        // Check for the "close" message to terminate
        if (strcmp(message, "close\n") == 0) {
            printf("Connection closed by client.\n");
            break;
        }

        // Receive a message from the server
        if (recv(client_socket, message, sizeof(message), 0) <= 0) {
            perror("Error receiving message");
            break;
        }
        printf("Server: %s\n", message);
    }

    // Close the socket
    close(client_socket);

    return 0;
}


