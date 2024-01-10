#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void deleteAndCreateCopiesDirectory(const char *dir)
{
    // Check if "Copies" directory exists
    struct stat dirStat;
    if (stat(dir, &dirStat) == 0 && S_ISDIR(dirStat.st_mode))
    {
        // Delete existing "Copies" directory and its contents
        system("rm -r Copies");
    }
    // Create a new "Copies" directory
    mkdir(dir, 0755);
}

int main(int argc, char **argv)
{

    /*
    You are expected to make use of File Management
    syscalls for this part.

    **INPUT**
    Filename will be given as input from the command line.
    */

    // Write your code here

    // 1) creates COPIES directory if its not there
    // U-> user, G->group, O->others
    //  mkdir("Copies", S_IRWXU | S_IRWXG | S_IRWXO); //symbolic notation
    char *dir = "Copies";
    // mkdir(dir, 0777); // octal notation ?
    deleteAndCreateCopiesDirectory(dir);

    // 2) opens input file
    int f1;
    f1 = open(argv[1], O_RDONLY, 0);

    // 3) create output file name
    char *out, *a;
    char *input_string;

    out = (char *)malloc(1000 * sizeof(char));
    input_string = argv[1];

    char *dot_position = strrchr(input_string, '.');
    size_t filename_length = dot_position - input_string;
    strncpy(out, input_string, filename_length);
    out[filename_length] = '\0';

    strcat(out, "_reverse.txt");
    // printf("Output string: %s\n", out);

    // 4) get permissions of og file
    struct stat st;
    if (stat(argv[1], &st) == -1)
    {
        perror("Error getting file status");
        return 1;
    }

    mode_t permissions = st.st_mode & 0777;
    // printf("File permissions: %o\n", permissions);

    // 5)create output file in Copies dir
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s", dir, out);

    int output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (output_fd == -1)
    {
        perror("Error creating output file");
        return 1;
    }

    // 6)getting file info
    double size;
    size = st.st_size;
    // printf("file size: %f\n", size);




    // WITHOUT CHUNKING (KINDA SLOWER)

    // // 7)positioning curson at offset of -1 from eof
    // int cursor = lseek(f1, -1, SEEK_END);

    // double perc = 0, total;
    // // printf("%lf%%\n", perc);

    // // 8)reverse file
    // char buffer;
    // while (cursor != -1)
    // {
    //     // read a character from input file
    //     ssize_t bytes_read = read(f1, &buffer, 1);

    //     total += 1;
    //     perc = (total / size) * 100;
    //     // printf("\r%.2lf%%", perc);

    //     // write the character to output file
    //     ssize_t bytes_written = write(output_fd, &buffer, 1);
    //     // move cursor back by 2 bytes (1 char)
    //     cursor = lseek(f1, -2, SEEK_CUR);
    // }




    // WITH CHUNKING (MUCH FASTER)

    char buffer[1024]; // Chunk size
    ssize_t bytes_read;
    off_t offset = lseek(f1, 0, SEEK_END);

    while (offset > 0)
    {
        // Calculate the size of the chunk
        //see if it's the last chunk
        ssize_t chunk_size = sizeof(buffer);
        if (offset < chunk_size)
        {
            chunk_size = offset;
        }

        // Move the offset back by the chunk size
        offset -= chunk_size;

        // Seek to the calculated offset
        lseek(f1, offset, SEEK_SET);

        // Read the chunk
        bytes_read = read(f1, buffer, chunk_size);

        // Reverse the chunk
        for (ssize_t i = 0; i < bytes_read / 2; i++)
        {
            char temp = buffer[i];
            buffer[i] = buffer[bytes_read - i - 1];
            buffer[bytes_read - i - 1] = temp;
        }

        // Write the reversed chunk to the output file
        ssize_t bytes_written = write(output_fd, buffer, bytes_read);
    }

    close(f1);
    close(output_fd);
    // close(dir);

    return 0;
}