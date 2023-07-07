#ifndef PIPE_MODULE_H
#define PIPE_MODULE_H

#include <stdbool.h>

/**
 * Copies the content of one file to another using a pipe.
 *
 * sourceFile      The path of the source file.
 * destinationFile The path of the destination file.
 * @return         `true` if the copy operation is successful, `false` otherwise.
 */
bool copyFileContent(const char *sourceFile, const char *destinationFile);

/**
 * Creates a named pipe with the given name.
 *
 * pipeName  The name of the named pipe.
 * isReader  Specifies if the pipe will be used for reading (`true`) or writing (`false`).
 * @return   `true` if the named pipe creation is successful, `false` otherwise.
 */
bool createNamedPipe(const char *pipeName, bool isReader);

/**
 * Uses a named pipe for communication.
 *
 * pipeName  The name of the named pipe.
 * message   The message to be sent or received through the pipe.
 * mode      The mode of the pipe (O_RDONLY for reading, O_WRONLY for writing).
 * @return   `0` if the operation is successful, `-1` otherwise.
 */
int useNamedPipe(const char *pipeName, const char *message, int mode);

#endif
