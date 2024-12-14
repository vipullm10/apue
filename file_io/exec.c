#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    printf("\narg count : %d", argc);
    printf("\n%s,%s", argv[0], argv[1]);
    if (argc < 2)
    {
        printf("\nPlease pass the two file descriptors");
        exit(EXIT_FAILURE);
    }
    int fileFd = atoi(argv[0]);
    int dupFd = atoi(argv[1]);
    printf("\nFile Descriptor is %d", fileFd);

    // we will be running this program with the help of the execv system call from another program
    // we are assuming this file descriptor is left open
    // we try to read the data from this file descriptor

    // first we set the offset of this file to the beginning
    off_t currentOffset = lseek(dupFd, 0, SEEK_SET);

    if (currentOffset == (off_t)-1)
    {
        perror("Error in lseek");
        exit(EXIT_FAILURE);
    }

    char readBuffer[4096];
    ssize_t bytesRead = 0;

    while ((bytesRead = read(dupFd, readBuffer, 4096)) > 0)
    {
        printf("%s", readBuffer);
    }
    if (bytesRead < 0)
    {
        perror("Error in reading file");
        exit(EXIT_FAILURE);
    }

    close(fileFd);
    close(dupFd);
}