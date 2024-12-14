#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dirent DIRENT;
#define BUFFERSIZE 4096
#define MAX_PATH_LENGTH 300

void printDirectoryInfo(char *startDirName, int tabIndex);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Please specify the starting directory name\n");
        exit(EXIT_FAILURE);
    }
    printDirectoryInfo(argv[1], 0);
}

void printDirectoryInfo(char *startDirName, int tabIndex)
{
    // Create a buffer for the directory name with tabs
    char directoryName[BUFFERSIZE];
    memset(directoryName, '\t', tabIndex); // Fill with tabs
    snprintf(directoryName + tabIndex, BUFFERSIZE - tabIndex, "%s", startDirName);
    printf("%s :\n", directoryName);

    DIR *dir = opendir(startDirName);
    if (!dir)
    {
        char buff[BUFFERSIZE];
        memset(buff, '\t', tabIndex); // Fill with tabs
        snprintf(buff + tabIndex, BUFFERSIZE - tabIndex, "Unable to open directory: %s", startDirName);
        perror(buff);
        return;
    }

    DIRENT *dirEntPointer;
    while ((dirEntPointer = readdir(dir)) != NULL)
    {
        if (strcmp(dirEntPointer->d_name, ".") == 0 || strcmp(dirEntPointer->d_name, "..") == 0)
            continue; // Skip current and parent directory entries

        if (dirEntPointer->d_type == DT_DIR) // Check if it's a directory
        {
            char subDirectoryRelativePath[MAX_PATH_LENGTH];
            snprintf(subDirectoryRelativePath, sizeof(subDirectoryRelativePath), "%s/%s", startDirName, dirEntPointer->d_name);
            printDirectoryInfo(subDirectoryRelativePath, tabIndex + 1);
        }
        else if (dirEntPointer->d_type == DT_REG)
        {
            char fileNameBuff[MAX_PATH_LENGTH];
            memset(fileNameBuff, 0, sizeof(fileNameBuff));
            memset(fileNameBuff, '\t', tabIndex + 1);
            snprintf(fileNameBuff + tabIndex + 1, MAX_PATH_LENGTH - tabIndex + 1, "%s", dirEntPointer->d_name);
            printf("%s\n", fileNameBuff);
        }
    }

    closedir(dir); // Always close the directory when done
}
