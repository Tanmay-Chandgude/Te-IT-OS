//7A_2FIFO.c

#include<stdio.h>
#include<fcntl.h>      // Required for file control operations
#include<sys/stat.h>   // Required for mkfifo (making FIFO files)
#include<sys/types.h>  // Required for file operations
#include<unistd.h>     // Required for system calls like read and write
#include<string.h>     // Required for string manipulation functions

int main()
{
    int fd, fd1;            // File descriptors for reading and writing
    char * myfifo = "myfifo";   // Name of the first FIFO (named pipe)
    char * myfifo1 = "myfifo1"; // Name of the second FIFO (named pipe)
    char buf[1024], ch[400];   // Buffers to store data received and written

    int words=1, character=0, line=1, i=0, j=0;  // Counters for words, characters, lines, and indices
    FILE *fp;  // File pointer for reading and writing to files

    // Create the FIFO file with read/write permissions (0777 allows read/write for all users)
    mkfifo(myfifo1, 0777);

    // Open the first FIFO for reading data from the pipe
    fd = open(myfifo, O_RDONLY);
    
    // Read data from the FIFO and store it in 'buf' (up to 1024 bytes)
    read(fd, buf, 1024);

    // Print the first message received from the FIFO
    printf("\nFirst message received: \n\n%s\n\n", buf);
    
    // Process the received message to count words, characters, and lines
    while(buf[i] != '\0')   // Iterate through each character in the received message
    {
        // Count words: Each time a space is encountered, it indicates a new word
        while(buf[i] == ' ') 
        {
            words++;  // Increment the word count
            i++;      // Move to the next character
        }

        // Count lines: Each time a newline is encountered, it indicates a new line
        while(buf[i] == '\n') 
        {
            line++;   // Increment the line count
            i++;      // Move to the next character
        }

        i++;    // Move to the next character
        character++;  // Increment the character count for every character
    }

    // Print the final word, line, and character counts
    printf("\nTotal Words := %d\n", words);
    printf("\nTotal Lines := %d\n", line);
    printf("\nTotal Characters := %d\n", character);

    // Open or create "test.txt" for writing
    fp = fopen("test.txt", "w+");

    // Write the statistics (word count, line count, and character count) to the file
    fprintf(fp, "\nTotal Words := %d\n", words);
    fprintf(fp, "\nTotal Lines := %d\n", line);
    fprintf(fp, "\nTotal Characters := %d\n", character);

    // Close the file after writing the data
    fclose(fp);  
    
    // Reopen "test.txt" for reading
    fp = fopen("test.txt", "r");

    // Read the content of the file into the 'ch' array
    while (!feof(fp))  // While not at the end of the file
    {
        ch[j] = fgetc(fp);  // Get a character from the file
        j++;                // Increment the index
    }

    // Close the file after reading
    fclose(fp);

    // Close the first FIFO file descriptor (no longer needed)
    close(fd);

    // Remove the first FIFO file from the file system
    unlink(myfifo);

    // Open the second FIFO for writing data into it
    fd1 = open(myfifo1, O_WRONLY);

    // Write the contents of 'ch' (the text read from "test.txt") to the second FIFO
    write(fd1, ch, strlen(ch));

    // Close the second FIFO after writing the data
    close(fd1);

    return 0;  // End of the program
}
