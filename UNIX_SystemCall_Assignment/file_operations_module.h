#ifndef FILE_OPERATIONS_MODULE_H
#define FILE_OPERATIONS_MODULE_H

#include <stdbool.h>

// Function to create a file with the specified filename and permissions
bool createFile(const char *filename, mode_t permissions);

// Function to read data from a file
// Parameters:
//   - filename: The name of the file to read from
//   - offset: The offset in bytes from where to start reading
//   - count: The number of bytes to read
//   - buffer: The buffer to store the read data
// Returns: The number of bytes read, or -1 if an error occurred
ssize_t readData(const char *filename, off_t offset, size_t count, char *buffer);

// Function to write data to a file
// Parameters:
//   - filename: The name of the file to write to
//   - offset: The offset in bytes from where to start writing
//   - count: The number of bytes to write
//   - data: The data to write
// Returns: The number of bytes written, or -1 if an error occurred
ssize_t writeData(const char *filename, off_t offset, size_t count, const char *data);

// Function to display information about a file
// Parameters:
//   - filename: The name of the file to display information about
void displayInfo(const char *filename);

#endif
