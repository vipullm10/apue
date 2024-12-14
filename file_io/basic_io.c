#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <inttypes.h>

#define BUFFERSIZE 4096

void show_error(char *path, int fdToBeClosed, bool isFatal);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Please specify the absolute path to the working directory and the relative path to the file\n");
        exit(EXIT_FAILURE);
    }

    int directoryFd = -1;
    if ((directoryFd = open(argv[1], O_RDONLY | O_DIRECTORY)) == -1)
        show_error(argv[1], -1, true);

    int fileFd = -1;
    if ((fileFd = openat(directoryFd, argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
    {
        show_error(argv[2], directoryFd, true);
    }
    int duplicateFileFd = 0;
    if (fcntl(fileFd, F_DUPFD, duplicateFileFd) == -1)
    {
        close(directoryFd);
        close(fileFd);
        show_error("Error in duplicating fd", -1, true);
    }
    char readBuffer[BUFFERSIZE];
    size_t bytesRead = 0;

    while ((bytesRead = read(STDIN_FILENO, readBuffer, BUFFERSIZE)) > 0)
    {
        ssize_t bytesWritten;
        while (bytesRead > 0)
        {
            bytesWritten = write(fileFd, readBuffer, bytesRead);
            if (bytesWritten < 0)
            {
                show_error("File write", fileFd, true);
            }
            bytesRead -= bytesWritten;
        }
    }
    if (bytesRead < 0)
        show_error("STDIN", -1, false);

    off_t currentOffset = lseek(fileFd, 0, SEEK_CUR);
    if (currentOffset == (off_t)-1)
    {
        perror("lseek error");
    }
    else
    {
        printf("currentOffset is %" PRId64 "\n", currentOffset);
    }

    currentOffset = lseek(fileFd, 0, SEEK_SET);
    if (currentOffset == (off_t)-1)
    {
        perror("lseek error");
    }
    else
    {
        printf("currentOffset after SEEK_SET is %" PRId64 "\n", currentOffset);
    }

    while ((bytesRead = read(fileFd, readBuffer, BUFFERSIZE)) > 0)
    {
        write(STDOUT_FILENO, readBuffer, bytesRead);
    }

    close(directoryFd);
    close(fileFd);
    exit(EXIT_SUCCESS);
}

void show_error(char *path, int fdToBeClosed, bool isFatal)
{
    fprintf(stderr, "Error in opening: %s\n", path);
    perror("Details");
    if (fdToBeClosed >= 0)
        close(fdToBeClosed);
    if (isFatal)
        exit(EXIT_FAILURE);
}
