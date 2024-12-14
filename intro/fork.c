#include "apue.h"
#include <sys/wait.h>

static void sig_int(int); // our signal-catching function

int main(void)
{
    char buff[MAXLINE]; /*from apue.h*/
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%%");
    while (fgets(buff, MAXLINE, stdin) != NULL)
    {
        if (buff[strlen(buff) - 1] == '\n')
            buff[strlen(buff) - 1] = 0;

        if ((pid = fork()) < 0)
        {
            err_sys("fork error");
        }
        else if (pid == 0)
        { /*child , as fork returns 0 as pid to the child*/
            execlp(buff, buff, (char *)0);
            err_ret("Couldn't execute: %s", buff);
            exit(127);
        }
        /*parent*/
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%%");
    }
    exit(0);
}

void sig_int(int signo)
{
    printf("interrupt\n%% ");
}