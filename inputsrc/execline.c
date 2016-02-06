// Execute a program for every line in inputfile

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void error (char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int main ()
{
	// We are using stdin for input
	char* line = NULL;
	size_t length; // unused
	pid_t pid;
	
	while (getline(&line, &length, stdin) != -1) {
		
		// Create pipe
		int fd[2];
		if (pipe(fd) == -1) error("Couldn't create pipe");
		
		// Execute the command with ../lsa
		pid = fork();
		if (pid == -1) error("Couldn't fork");
		
		if (!pid) { // Child
			// Close write end of pipe
			close(fd[1]);
			dup2(fd[0], 0); // Dup pipe on stdin
			free(line);
			line = NULL;
			
			// Now execute lsa
			execl("../lsa", "../lsa", 0);
		}
		
		// Parent
		close(fd[0]);
		//dup2(fd[1], 1);
		
		// Write to child
		printf("Input: %s\n", line);
		dprintf(fd[1], "%s", line);
		
		free(line);
		line = NULL;
		
		// Wait for child
		int pid_status;
		if (waitpid(pid, &pid_status, 0) == -1) 
			error("Waiting for child process");
		
		printf("\n");
	}
	
	return 0;
}
