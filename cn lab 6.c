#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 1024

int main(int argc, char *argv[]) {
if (argc != 2) {
fprintf(stderr, "Usage: %s <port>\n", argv[0]);
exit(1);
}

int server_socket, new_socket, max_fd, client_sockets[MAX_CLIENTS];
fd_set readfds;
char message[MAX_MESSAGE_SIZE];
int opt = 1;
int port = atoi(argv[1]);

// Create a server socket
if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
perror("socket");
exit(1);
}

// Set socket options
if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
perror("setsockopt");
exit(1);
}

// Bind the server socket to a port
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(port);

if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
perror("bind");
exit(1);
}

// Listen for incoming connections
if (listen(server_socket, MAX_CLIENTS) < 0) {
perror("listen");
exit(1);
}

// Initialize client_sockets array and set them to 0
for (int i = 0; i < MAX_CLIENTS; i++) {
client_sockets[i] = 0;
}

// Add server socket to the set
FD_ZERO(&readfds);
FD_SET(server_socket, &readfds);
max_fd = server_socket;

printf("Chat server is listening on port %d...\n", port);

while (1) {
fd_set temp_fds = readfds;
int activity = select(max_fd + 1, &temp_fds, NULL, NULL, NULL);

if (activity < 0) {
perror("select");
exit(1);
}

// Check for incoming connection
if (FD_ISSET(server_socket, &temp_fds)) {
if ((new_socket = accept(server_socket, NULL, NULL)) < 0) {
perror("accept");
exit(1);
}

// Add new connection to the client_sockets array
for (int i = 0; i < MAX_CLIENTS; i++) {
if (client_sockets[i] == 0) {
client_sockets[i] = new_socket;
break;
}
}

// Add new socket to the set
FD_SET(new_socket, &readfds);
if (new_socket > max_fd) {
max_fd = new_socket;
}

printf("New connection, socket fd is %d\n", new_socket);
}

// Handle data from clients
for (int i = 0; i < MAX_CLIENTS; i++) {
int sd = client_sockets[i];

if (FD_ISSET(sd, &temp_fds)) {
int valread = read(sd, message, MAX_MESSAGE_SIZE);

if (valread == 0) {
// Client disconnected
getpeername(sd, (struct sockaddr*)&server_addr, (socklen_t*)&port);
printf("Host disconnected, IP %s, port %d\n", inet_ntoa(server_addr.sin_addr), port);
close(sd);
client_sockets[i] = 0;
} else {
// Broadcast message to all other clients
message[valread] = '\0';
for (int j = 0; j < MAX_CLIENTS; j++) {
if (client_sockets[j] != 0 && client_sockets[j] != sd) {
send(client_sockets[j], message, strlen(message), 0);
}
}
}
}
}
}

return 0;
}


