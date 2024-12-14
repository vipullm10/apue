#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

    if (rename(argv[1], argv[2]) < 0)
    {
        perror("Error while rename");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}