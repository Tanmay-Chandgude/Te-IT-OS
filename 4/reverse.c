// testb.c

#include<stdio.h>  // Include the standard input-output library
#include<stdlib.h> // Include the standard library for using exit() and EXIT_SUCCESS
#include<string.h> // Include the string library for string manipulation functions like strlen()

// Main function which accepts command-line arguments
int main(int argc, char *argv[])
{
  // Calculate the length of the first command-line argument
  int length = strlen(argv[1]);

  // Print a message indicating the program's output
  printf("Program 2 value of n= \n");

  // Loop through the characters of the first argument in reverse order
  for(int i = length - 1; i >= 0; i--)
  {
    // Print the numeric value of each character (converting char to int by subtracting 48)
    // ASCII value of '0' is 48, so subtracting 48 converts the char to its integer value
    printf("%d ", argv[1][i] - 48);
  }

  // Exit the program with a success code
  exit(EXIT_SUCCESS);
}
