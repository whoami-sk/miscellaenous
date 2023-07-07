#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "file_operations_module.h"
#include "pipe_module.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [arguments]\n", argv[0]);
        return 1;
    }

    char *command = argv[1];

    if (strcmp(command, "createFile") == 0) {
        // Check the number of arguments
        if (argc != 4) {
            printf("ERROR: Wrong No. Of Arguments. \n");
            printf("Usage: %s createFile <filename> <permissions>\n", argv[0]);
            return 1;
        }

        char *filename = argv[2];
        mode_t permissions = strtol(argv[3], NULL, 8);

        // Call the createFile function and check its return value
        if (createFile(filename, permissions)) {
            printf("File created successfully.\n");
        } else {
            printf("Failed to create file.\n");
        }
    } else if (strcmp(command, "readData") == 0) {
        // Check the number of arguments
        if (argc != 5) {
            printf("ERROR: Wrong No. Of Arguments. \n");
            printf("Usage: %s readData <filename> <offset> <count>\n", argv[0]);
            return 1;
        }

        char *filename = argv[2];
        off_t offset = strtol(argv[3], NULL, 10);
        size_t count = strtol(argv[4], NULL, 10);
        char buffer[count];

        // Call the readData function and check its return value
        ssize_t bytesRead = readData(filename, offset, count, buffer);
        if (bytesRead > 0) {
            printf("Read %ld bytes from the file:\n", bytesRead);
            printf("%.*s\n", (int)bytesRead, buffer);
        } else {
            printf("File is EMPTY!\n");
        }
    } else if (strcmp(command, "writeData") == 0) {
        // Check the number of arguments
        if (argc != 6) {
            printf("ERROR: Wrong No. Of Arguments. \n");
            printf("Usage: %s writeData <filename> <offset> <count> <data>\n", argv[0]);
            return 1;
        }

        char *filename = argv[2];
        off_t offset = strtol(argv[3], NULL, 10);
        size_t count = strtol(argv[4], NULL, 10);
        char *data = argv[5];

        // Call the writeData function and check its return value
        ssize_t bytesWritten = writeData(filename, offset, count, data);
        if (bytesWritten > 0) {
            printf("Written %ld bytes to the file.\n", bytesWritten);
        } else {
            printf("Failed to write data to the file.\n");
        }
    } else if (strcmp(command, "displayInfo") == 0) {
        // Check the number of arguments
        if (argc != 3) {
            printf("ERROR: Wrong No. Of Arguments. \n");
            printf("Usage: %s displayInfo <filename>\n", argv[0]);
            return 1;
        }

        char *filename = argv[2];

        // Call the displayInfo function
        displayInfo(filename);
    } else if (strcmp(command, "copyFileContent") == 0) {
        // Check the number of arguments
        if (argc != 4) {
            printf("ERROR: Wrong No. Of Arguments. \n");
            printf("Usage: %s copyFileContent <source_file> <destination_file>\n", argv[0]);
            return 1;
        }

        char *sourceFile = argv[2];
        char *destinationFile = argv[3];

        // Call the copyFileContent function and check its return value
        if (copyFileContent(sourceFile, destinationFile)) {
            printf("File copied successfully.\n");
        } else {
            printf("Failed to copy file.\n");
        }
    } else if (strcmp(command, "createNamedPipe") == 0) {
        // Check the number of arguments
        if (argc != 4) {
            printf("ERROR: Wrong No. Of Arguments. \n");
            printf("Usage: %s createNamedPipe <pipe_name> <is_reader>\n", argv[0]);
            return 1;
        }

        char *pipeName = argv[2];
        bool isReader = strtol(argv[3], NULL, 10);

        // Call the createNamedPipe function and check its return value
        if (createNamedPipe(pipeName, isReader)) {
            printf("Named pipe created successfully.\n");
        } else {
            printf("Failed to create named pipe.\n");
        }
    } else if (strcmp(command, "useNamedPipe") == 0) {
        // Check the number of arguments
        if (argc != 5) {
            printf("ERROR: Wrong No. Of Arguments. \n");
            printf("Usage: %s useNamedPipe <pipe_name> <message> <mode (0-read, 1-write)>\n", argv[0]);
            return 1;
        }

        char *pipeName = argv[2];
        char *message = argv[3];
        int mode = atoi(argv[4]);  // Parse the mode from the command-line argument

        // Check the validity of the pipe mode
        if (mode == O_RDONLY || mode == O_WRONLY) {
            // Call the useNamedPipe function and check its return value
            if (useNamedPipe(pipeName, message, mode) == 0) {
                printf("Message sent/received through named pipe.\n");
            } else {
                printf("Failed to communicate through named pipe.\n");
            }
        } else {
            printf("Invalid pipe mode. Use O_RDONLY or O_WRONLY.\n");
            return 1;
        }
    } else {
        printf("Invalid command.\n");
        return 1;
    }

    return 0;
}

