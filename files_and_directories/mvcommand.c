#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Invalid input , please make sure new / existing paths are specified");
        exit(EXIT_FAILURE);
    }

    // there can be two possisble cases , existing file is a regular file / existing file is a directory
    // if the existing file is a regular file , then the new file cannot be a directory .
    // The mv command allows us to move a file into a directory , so we must make sure to append the file name to the path in case the destination path is a directory
    // if the new file exists already , then it is unlinked and replaced by the existing file . in that case we need the read and execute permission on the directory
    // beacuse it's as if we are deleting the new file which already exitsts

    // if the existing file is a directory , then the new file must be a directory , it cannot be a regular file
    // The mv command allows us to move an existing directory inside another directory
}