#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please provide file path as argument\n");
        exit(EXIT_FAILURE);
    }

    if (access(argv[1], R_OK) < 0)
    {
        char buff[4096];
        snprintf(buff, 4096, "Read error for file %s\n", argv[1]);
        perror(buff);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Read access OK\n");
    }

    if (open(argv[1], O_RDWR) < 0)
    {
        char buff[4096];
        snprintf(buff, 4096, "Open error for file %s\n", argv[1]);
        perror(buff);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Open for reading OK \n");
    }

    exit(0);
}