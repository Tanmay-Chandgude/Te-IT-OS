//7A_1FIFO

#include<stdio.h>      // Header file for standard input/output functions
#include<fcntl.h>      // Header file for file control options
#include<sys/stat.h>   // Header file for defining constants like file permissions
#include<unistd.h>     // Header file for UNIX system calls like open(), close(), and read()

int main()
{
    int fd, fd1;           // Declare file descriptors fd (for writing) and fd1 (for reading)
    char * myfifo = "myfifo";       // Declare a pointer to the first FIFO file name (for writing)
    char * myfifo1 = "myfifo1";     // Declare a pointer to the second FIFO file name (for reading)
    char buf[1024];         // Buffer to hold data read from the FIFO

    // Create a FIFO named 'myfifo' with read-write permission for the owner and group (0666)
    mkfifo(myfifo, 0666);   
    
    // Create another FIFO named 'myfifo1' with read-write permission for everyone (0777)
    mkfifo(myfifo1, 0777);  

    // Open the first FIFO 'myfifo' for writing only (O_WRONLY)
    fd = open(myfifo, O_WRONLY);

    // Write a message to the FIFO 'myfifo'
    write(fd, "Hello All.. \nWelcome... \nto PES MCOE \nPune. \nMaharashtra \nIndia.", sizeof("Hello All.. \nWelcome... \nto PES MCOE \nPune. \nMaharashtra \nIndia."));

    // Close the write end of the FIFO
    close(fd);

    // Delete the FIFO 'myfifo' (it is no longer needed after writing)
    unlink(myfifo);

    // Open the second FIFO 'myfifo1' for reading only (O_RDONLY)
    fd1 = open(myfifo1, O_RDONLY);

    // Read data from the FIFO 'myfifo1' into the buffer 'buf'
    read(fd1, buf, sizeof(buf));

    // Print the data read from the FIFO (the message written earlier)
    printf("%s", buf);

    // Delete the FIFO 'myfifo1' (it is no longer needed after reading)
    unlink(myfifo1);

    // Close the read end of the FIFO
    close(fd1);

    return 0; // Exit the program
}
