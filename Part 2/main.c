#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void toLowerCase(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = tolower(src[i]);
        i++;
    }
    dest[i] = '\0'; // Null-terminate the destination string
}

void toUpperCase(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = toupper(src[i]);
        i++;
    }
    dest[i] = '\0'; // Null-terminate the destination string
}

int main(int argc, char **argv)
{

    /*
    When fork creates a child process B as a copy of A
    the return value of fork is set as 0 in B where as
    it is set to the process ID of B in parent process A.

    You can use this return value to differentiate between the child and parent process.

    **INPUT**
    String will be given as input from command line.
    */

    // Write your code here
    char *inputString = argv[1]; // first argument (index 1) is the input string
    int length = strlen(inputString);
    char convertedString[length + 1]; // Add 1 for null terminator

    // printf("Input string: %s with pid: %d\n", inputString, (int)getpid());

    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child
        toLowerCase(convertedString, inputString);
        printf("=== Child Process ===\n");
        printf("%s\n", convertedString);
    }
    else
    {
        toUpperCase(convertedString, inputString);
        printf("=== Parent Process ===\n");
        printf("%s\n", convertedString);
    }

    return 0;
}