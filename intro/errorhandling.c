#include <errno.h>
#include "apue.h"
#include <stdarg.h>
#include <stdio.h>
#include <sys/msg.h>
static void vout(char *buff, char *fmt, ...);

int main(int argc, char *argv[])
{

    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = EACCES;
    perror(argv[0]);
    fflush(stderr);
    char printBuff[MAXLINE];
    char *fmt = "%s %s %s";
    char *stringArr[] = {"Sat", "Sun", "Mon"};
    vout(printBuff, fmt, stringArr[0], stringArr[1]);
    printf("%s", printBuff);
    char *str = "Hello world";
    size_t str_len = strlen(str);
    printf("Length of %s is %zu", str, str_len);
}

void vout(char *buff, char *fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    vsnprintf(buff, MAXLINE, fmt, list);
    va_end(list);
}
