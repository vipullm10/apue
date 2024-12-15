#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

#if 0
    if (argc < 3)
    {
        printf("Please specify source and destination ");
        exit(EXIT_FAILURE);
    }
    if (link(argv[1], argv[2]) < 0)
    {
        char buff[4096];
        if (errno == EEXIST)
            snprintf(buff, 4096, "Error in link system call");
        else
            snprintf(buff, 4096, "Error in link system call");
        perror(buff);
        exit(EXIT_FAILURE);
    }
    if (unlink(argv[1]) < 0)
    {
        perror("Error in unlink");
        exit(EXIT_FAILURE);
    }
#endif

    // if (rename(argv[1], argv[2]) < 0)
    // {
    //     perror("Error while rename");
    //     exit(EXIT_FAILURE);
    // }
    struct stat statBuff;
    stat(argv[2], &statBuff);
    if (S_ISDIR(statBuff.st_mode))
    {
        printf("%s is a directory", argv[2]);
    }
    exit(EXIT_SUCCESS);
}