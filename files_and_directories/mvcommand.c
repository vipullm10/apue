#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

char *getFileNameFromPath(char fullPath[])
{
    char *copy = strdup(fullPath);
    char *token = strtok(copy, "/");
    char *fileName = NULL;
    while (token != NULL)
    {
        fileName = token;
        token = strtok(NULL, "/");
    }
    char *result = strdup(fileName);
    free(copy);
    return result;
}

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

    // first we obtain information about the exiting file
    struct stat sourceStat;
    if (stat(argv[1], &sourceStat) < 0)
    {
        // show an error and exit if the stat system call fails
        char errBuff[4096];
        snprintf(errBuff, 4096, "Failed to call stat for %s", argv[1]);
        perror(errBuff);
        exit(EXIT_FAILURE);
    }

    // now we must check if the new file is a directory that exitsts

    size_t len = strlen(argv[2]);
    char destination[4096];
    memcpy(destination, argv[2], len);
    struct stat destinationStat;
    if (stat(destination, &destinationStat) == 0)
    {
        // this means the stat system call was successfully executed
        // now we check the type of the destination
        if (S_ISDIR(destinationStat.st_mode))
        {
            // this means that the destination is a directory and it exists , so we must append the source file/directory name to this path to move the file/directory inside the directory
            char *fileName = getFileNameFromPath(argv[1]);
            snprintf(destination + len, 4096 - len, "/%s", fileName);
            free(fileName);
        }
    }
    // at this point , if the stat system call failed , that means the destination path doesn't exist or something else went wrong
    //, in that case we pass the paths to the rename function as it is
    // if the system call passed , and the check that the destination is a directory failed , it means that the destination is a file that already exists
    //, in that case we pass the paths to the rename function as it is
    if (rename(argv[1], destination) < 0)
    {
        perror("Error in rename");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}