#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Function to copy the content of one file to another using a pipe
bool copyFileContent(const char *sourceFile, const char *destinationFile) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return false;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("ERROR! creating child process (fork).");
        return false;
    }

    if (pid == 0) {
        // Child process - read from the pipe and write to the destination file
        close(pipefd[1]);  // Close the write end of the pipe

        int destinationFd = open(destinationFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (destinationFd == -1) {
            perror("ERROR! opening destination file.");
            close(pipefd[0]);
            return false;
        }

        ssize_t bytesRead;
        char buffer[4096];

        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            ssize_t bytesWritten = write(destinationFd, buffer, bytesRead);
            if (bytesWritten == -1) {
                perror("ERROR! writing to destination file.");
                close(pipefd[0]);
                close(destinationFd);
                return false;
            }
        }

        close(pipefd[0]);
        close(destinationFd);
        return true;
    } else {
        // Parent process - read from the source file and write to the pipe
        close(pipefd[0]);  // Close the read end of the pipe

        int sourceFd = open(sourceFile, O_RDONLY);
        if (sourceFd == -1) {
            perror("ERROR! opening source file.");
            close(pipefd[1]);
            return false;
        }

        ssize_t bytesRead;
        char buffer[4096];

        while ((bytesRead = read(sourceFd, buffer, sizeof(buffer))) > 0) {
            ssize_t bytesWritten = write(pipefd[1], buffer, bytesRead);
            if (bytesWritten == -1) {
                perror("ERROR! writing to pipe.");
                close(sourceFd);
                close(pipefd[1]);
                return false;
            }
        }

        close(sourceFd);
        close(pipefd[1]);

        // Wait for the child process to finish
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("ERROR! while waiting for child process.");
            return false;
        }

        return true;
    }
}


// Function to create a named pipe with the given name and mode
int createNamedPipe(const char *pipeName, int mode) {
    int pipeFd;

    // Create the named pipe with read and write permissions for all users
    if (mkfifo(pipeName, 0666) == -1) {
        perror("ERROR! creating named pipe");
        return -1;
    }

    // Open the named pipe in the specified mode
    if (mode == O_RDONLY) {
        pipeFd = open(pipeName, O_RDONLY | O_NONBLOCK);
    } else if (mode == O_WRONLY) {
        pipeFd = open(pipeName, O_WRONLY | O_NONBLOCK);
    } else {
        fprintf(stderr, "Invalid pipe mode.\n");
        return -1;
    }

    if (pipeFd == -1) {
        perror("ERROR! opening named pipe.");
        return -1;
    }

    return pipeFd;
}

// Function to use a named pipe for communication
int useNamedPipe(const char *pipeName, const char *message, int mode) {
    int pipeFd;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    // Open the named pipe in the specified mode
    if (mode == O_RDONLY) {
        pipeFd = open(pipeName, O_RDONLY);
    } else if (mode == O_WRONLY) {
        pipeFd = open(pipeName, O_WRONLY);
    } else {
        fprintf(stderr, "Invalid pipe mode.\n");
        return -1;
    }

    if (pipeFd == -1) {
        perror("ERROR! opening named pipe.");
        return -1;
    }

    if (mode == O_WRONLY) {
        // Write the message to the named pipe
        bytesWritten = write(pipeFd, message, strlen(message));
        if (bytesWritten == -1) {
            perror("ERROR! writing to named pipe.");
            close(pipeFd);
            return -1;
        }
        printf("Message sent: %s\n", message);
    } else if (mode == O_RDONLY) {
        // Read the message from the named pipe
        bytesRead = read(pipeFd, buffer, BUFFER_SIZE - 1);
        if (bytesRead == -1) {
            perror("ERROR! reading from named pipe.");
            close(pipeFd);
            return -1;
        }
        buffer[bytesRead] = '\0';
        printf("Received message: %s\n", buffer);
    }

    close(pipeFd);
    return 0;
}
