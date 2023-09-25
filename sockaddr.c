// Accept connection request from client in cliAddr
// socket structure
int clientSocket = accept(
	int sockfd, (struct sockaddr*) 	(struct sockaddr_in &cliAddr), socklen_t &addr_size);

// Make a child process by fork() and check if child
// process is created successfully
 if (( pid_t childpid = fork()) == 0) 
{
	// Send a confirmation message to the client for
	// successful connection
	send(clientSocket, "hi client", strlen("hi client"),0);
}
