#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please give the full path to the file");
        exit(EXIT_FAILURE);
    }

    int fileFd = open(argv[1], O_RDWR);
    if (fileFd == -1)
    {
        char buff[4096];
        snprintf(buff, 4096, "Error in opening %s", argv[1]);
        perror(buff);
        exit(EXIT_FAILURE);
    }

    off_t noOfBytes = lseek(fileFd, 0, SEEK_END);
    if (noOfBytes == (off_t)-1)
    {
        perror("Error in seeking ");
        exit(EXIT_FAILURE);
    }
    printf("No of bytes written for %s is %lld \n", argv[1], noOfBytes);

    noOfBytes = lseek(fileFd, 0, SEEK_SET);
    if (noOfBytes == (off_t)-1)
    {
        perror("Error in seeking ");
        exit(EXIT_FAILURE);
    }

    int flags = -1;
    if ((flags = fcntl(fileFd, F_GETFL)) < 0)
    {
        char buff[4096];
        snprintf(buff, 4096, "fcntl error for fd : %d", fileFd);
        perror(buff);
        exit(EXIT_FAILURE);
    }
    switch (flags & O_ACCMODE)
    {
    case O_RDONLY:
        printf("read only");
        break;
    case O_WRONLY:
        printf("write only");
        break;
    case O_RDWR:
        printf("read and write");
        break;
    case O_EXEC:
        printf("exec only");
        break;
    case O_SEARCH:
        printf("search only");
        break;
    default:
        printf("Unknown access mode");
    }

    int dupFd = 0;
    if ((dupFd = fcntl(fileFd, F_DUPFD_CLOEXEC, fileFd)) < 0)
    {
        char buff[4096];
        snprintf(buff, 4096, "Error whhile duplicating fd : %d", fileFd);
        perror(buff);
    }

    printf("\nfileFd : %d , dupFd : %d\n", fileFd, dupFd);
    printf("Attempting to read the contents of file represented by the file descriptor : %d\n", dupFd);

    char readBuffer[4096];
    ssize_t bytesRead = 0;
    while ((bytesRead = read(dupFd, readBuffer, 4096)) > 0)
    {
        printf("%s", readBuffer);
    }

#if 0
    char fd1[20];
    char fd2[20];

    snprintf(fd1, 19, "%d", fileFd);
    snprintf(fd2, 19, "%d", dupFd);

    char *args[] = {fd1, fd2, NULL};

    execv("/Users/vipuldevnani/apue/file_io/exec_exe", args);

    perror("exec error");

    close(fileFd);
    close(dupFd);
#endif
    int dupFdFlags = fcntl(dupFd, F_GETFL, 0);
    if ((dupFdFlags & O_APPEND) != O_APPEND)
    {
        printf("\n dupFd : %d is not openend in append mode", dupFd);
        dupFdFlags |= O_APPEND;
        if ((fcntl(dupFd, F_SETFL, dupFdFlags)) < 0)
        {
            char buff[4096];
            snprintf(buff, 4096, "Cannot set O_APPEND flag on fd : %d", dupFd);
            perror(buff);
            exit(EXIT_FAILURE);
        }
        dupFdFlags = fcntl(dupFd, F_GETFL, 0);
        if ((dupFdFlags & O_APPEND) == O_APPEND)
        {
            printf("\nO_APPEND flag set successfully for fd %d\n", dupFd);
        }
    }

    char readBuff[4096];
    bytesRead = 0;
    off_t currentOffset = lseek(dupFd, 0, SEEK_SET);
    while ((bytesRead = read(dupFd, readBuff, 4096)) > 0)
    {
        printf("%s", readBuff);
    }
    currentOffset = lseek(dupFd, 0, SEEK_SET);
    char buff[30] = {"Hello world replaced"};
    write(dupFd, buff, 30);
}