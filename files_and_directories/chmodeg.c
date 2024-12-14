#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct stat statbuf;
    /*turn on set-group ID and trun off group-execute*/
    if (stat("foo", &statbuf) < 0)
    {
        perror("Error while calling stat for foo");
        exit(EXIT_FAILURE);
    }

    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    {
        perror("chmod error for foo");
        exit(EXIT_FAILURE);
    }

    /*set absolute mode to rw-r--r--*/
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
    {
        perror("chmod error for bar");
        exit(EXIT_FAILURE);
    }
}