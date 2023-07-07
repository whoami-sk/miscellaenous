/*
 * 
 * This program provides various functionalities for file and pipe operations through command-line arguments.
 * It supports the following tasks:
 * 
 * 1. Create a file and named pipe with user-defined permissions.
 * 2. Read data from a file, allowing the user to specify the amount of data to read and the starting position.
 * 3. Write data to a file, allowing the user to specify the amount of data to write and the starting position.
 * 4. Display statistical information of a specified file, including owner, permissions, inode, and timestamps.
 * 5. Create an unnamed pipe to copy the content of one file to another file.
 * 6. Create a named pipe to enable communication between two processes, with the user specifying the purpose (read or write).
 * 
 * Usage:
 * gcc -o program main.c file_operations_module.c pipe_module.c      
 * ./program <command> [arguments]
 * 
 * Commands:
 * - createFile <file> <permissions>            : Create a file with the specified permissions.
 * - readData <file> <bytes> <position>         : Read a specified amount of data from a file starting from a given position.
 * - writeData <file> <bytes> <position> <data> : Write a specified amount of data to a file starting from a given position.
 * - displayInfo <file>                         : Display statistical information of a specified file.
 * - copyFileContent <source> <destination>     : Copy the content of one file to another using an unnamed pipe.
 * - createNamedPipe <pipe_name> <mode>         : Create the named pipe with read or write mode.
 * - useNamedPipe <name> <message> <read/write> : Create a named pipe for reading or writing. (0 for reading and 1 for writing).
 * 
 * 
 *
 *  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * ## createFile
 * Creates a new file with the specified name and permissions.
 * Usage: ./program createFile <filename> <permissions>
 * Example: ./program createFile myfile.txt 0644 
 * - `<filename>`   : The name of the file to be created.
 * - `<permissions>`: The permissions to set for the file, specified as an octal number (e.g., 0644).
 *
 *
 * ## readData
 * Reads data from a file starting from the specified offset and for the specified count.
 * Usage: ./program readData <filename> <offset> <count>
 * Example: ./program readData myfile.txt 0 100   
 * - `<filename>`: The name of the file from which to read data.
 * - `<offset>`  : The offset (in bytes) from which to start reading.
 * - `<count>`   : The number of bytes to read from the file.
 *
 *
 * ## writeData
 * Writes data to a file starting from the specified offset.  
 * Usage: ./program writeData <filename> <offset> <count> <data>
 * Example: ./program writeData myfile.txt 0 10 "Hello World"
 * - `<filename>`: The name of the file to which to write data.
 * - `<offset>`  : The offset (in bytes) from which to start writing.
 * - `<count>`   : The number of bytes to write to the file.
 * - `<data>`    : The data to write to the file.
 *
 *
 * ## displayInfo
 * Displays information about a file, such as its size, permissions, and modification time.
 * Usage: ./program displayInfo <filename>
 * Example: ./program displayInfo myfile.txt
 * - `<filename>`: The name of the file for which to display information.
 *
 *
 *
 * ## copyFileContent
 * Copies the content of one file to another file.
 * Usage: ./program copyFileContent <source_file> <destination_file>
 * Example: ./program copyFileContent source.txt destination.txt
 * - `<source_file>`     : The name of the file from which to copy content.
 * - `<destination_file>`: The name of the file to which to copy content.
 *
 *
 *
 * ## createNamedPipe
 * Creates a named pipe with the specified name and reader/writer mode.
 * Usage: ./program createNamedPipe <pipe_name> <mode>
 * Example: ./program createNamedPipe mypipe O_RDONLY   
 * - `<pipe_name>`: The name of the named pipe to create.
 * - `<is_reader>`: O_RDONLY or O_WRONLY
 *
 *
 *
 * ## useNamedPipe
 * Sends or receives a message through a named pipe.
 * Usage: ./program useNamedPipe <pipe_name> <message> <mode (0-read, 1-write)>
 * Example: ./program useNamedPipe mypipe "Hello" 1  
 * - `<pipe_name>`: The name of the named pipe to use.
 * - `<message>`  : The message to send or receive through the pipe.
 * - `<mode>`     : Set to 0 to read from the pipe or 1 to write to the pipe.
 *
 *  Note: For `useNamedPipe`, make sure you have already created the named pipe using the `createNamedPipe` command.
 */
 
 
