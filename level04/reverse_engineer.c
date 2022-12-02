#include <stdlib.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int pid = fork();

    char buf[32] = {0};

    if (pid == 0)
    {
        prctl(PR_SET_PDEATHSIG /*(1)*/, SIGHUP /*(1)*/); // kill child when parent dies
        ptrace(PTRACE_TRACEME /*(0)*/, 0, 0, 0); // (2) allow parent to trace child
        puts("Give me some shellcode, k");
        gets(buf); // (3) get input
    }
    else
    {
        int status;
        
        while (1)
        {
            wait(&status);
            if (WIFEXITED(status)) // if (status & 0x7f) == 0 // we see it's the def of this macro
            {
                puts("child is exiting...");
                return 0;
            }

            if (WIFSIGNALED(status)) // if (status & 0x7f) != 0
            {
                puts("child is exiting");
                return 0;
            }

            int word = ptrace(PTRACE_PEEKUSER /*(3)*/, pid, 44 /*(0x2c)*/, 0 /*Prolly end of va_arg*/);
            // read a word in process user area at offset 44
            if (word == 0xb) // if (word == 0xb)
            {
                puts("no exec() for you");
                kill(pid, SIGKILL /*(9)*/);
                return 0;
            }
        }
    }

    return 0;
}