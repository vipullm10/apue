#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#define BUFFERSIZE 4096

int main(int argc, char *argv[])
{
    long mins = LONG_MIN;
    pid_t processId = getpid();
    fprintf(stderr, "Process id : %d\n", processId);
    fflush(stdout);
    char readBuffer[BUFFERSIZE];
    char bytesRead[20]; // buffer to show the string "bytes read  : "
    char errorBuffer[BUFFERSIZE];
    size_t total_bytes_read = 0;
    if (snprintf(bytesRead, 13, "bytes read : ") < 0)
    {
        int len = snprintf(errorBuffer, BUFFERSIZE, "Error in snprintf : %s", strerror(errno));
        if (len > 0)
            write(STDERR_FILENO, errorBuffer, len);
        exit(0);
    }
    size_t n = 0;
    while ((n = read(STDIN_FILENO, readBuffer, BUFFERSIZE)) > 0)
    {
        total_bytes_read += n;
        write(STDOUT_FILENO, readBuffer, n);
    }
    if (n < 0)
    {
        int len = snprintf(errorBuffer, BUFFERSIZE, "Error in read : %s", strerror(errno));
        if (len > 0)
            write(STDERR_FILENO, errorBuffer, len);
        exit(0);
    }
    if (snprintf(bytesRead + 13, 5, "%zu\n", total_bytes_read) > 0)
    {
        write(STDERR_FILENO, bytesRead, 20);
    }
}