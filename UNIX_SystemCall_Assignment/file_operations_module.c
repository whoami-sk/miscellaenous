#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "file_operations_module.h"

// Function to create a file with the specified filename and permissions
bool createFile(const char *filename, mode_t permissions) {
    int fd = creat(filename, permissions);
    if (fd == -1) {
        perror("ERROR! in creating the File.");
        return false;
    }
    close(fd);
    return true;
}

// Function to read data from a file
ssize_t readData(const char *filename, off_t offset, size_t count, char *buffer) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("ERROR! Opening File. (Maybe check file permissions you are trying to open.)");
        return -1;
    }

    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("ERROR! while setting Offset.");
        close(fd);
        return -1;
    }

    ssize_t bytesRead = read(fd, buffer, count);
    if (bytesRead == -1) {
        perror("ERROR! while reading file.");
    }

    close(fd);
    return bytesRead;
}

// Function to write data to a file
ssize_t writeData(const char *filename, off_t offset, size_t count, const char *data) {
    int fd = open(filename, O_WRONLY);
    if (fd == -1) {
        perror("ERROR! Opening File. (Maybe check file permissions you are trying to open.");
        return -1;
    }

    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("ERROR! while setting Offset.");
        close(fd);
        return -1;
    }

    ssize_t bytesWritten = write(fd, data, count);
    if (bytesWritten == -1) {
        perror("ERROR! while writing file.");
    }

    close(fd);
    return bytesWritten;
}

// Function to display information about a file
void displayInfo(const char *filename) {
    struct stat fileStat;

    if (stat(filename, &fileStat) == -1) {
        perror("ERROR! while retrieving file info.");
        return;
    }

    printf("File: %s\n", filename);
    printf("Owner: %d\n", fileStat.st_uid);
    printf("Group: %d\n", fileStat.st_gid);
    printf("Permissions: %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    printf("Inode number: %lu\n", fileStat.st_ino);
    printf("Last access time: %s", ctime(&fileStat.st_atime));
    printf("Last modification time: %s", ctime(&fileStat.st_mtime));
    printf("Last status change time: %s", ctime(&fileStat.st_ctime));
}
