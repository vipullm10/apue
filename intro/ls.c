#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

typedef struct dirent DIRENT;

int main(int argc, char *argv[])
{
    greet();
    DIR *dp;
    DIRENT *dirp;
    if (argc != 2)
    {
        printf("usage is ls directory_name");
        exit(0);
    }
    if ((dp = opendir(argv[1])) == NULL)
    {
        printf("can't open %s", argv[1]);
        exit(0);
    }
    while ((dirp = readdir(dp)) != NULL)
        printf("%s,%c\n", dirp->d_name, dirp->d_type);
    closedir(dp);

    dp = opendir(argv[1]);
    if (!dp)
    {
        printf("Cant open %s", argv[1]);
        exit(0);
    }

    while ((dirp = readdir(dp)) != NULL)
        printf("%s,%c\n", dirp->d_name, dirp->d_type);

    closedir(dp);
    exit(0);
}