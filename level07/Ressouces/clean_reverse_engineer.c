#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void clear_stdin()
{
    while (getchar() != EOF);
}

unsigned int get_unum()
{
    int unum = 0;
    fflush(stdout);
    scanf("%u", &unum);
    clear_stdin();

    return unum;
}

int store_number(int *numbers)
{
    printf(" Number: ");
    unsigned int number = get_unum();
    printf(" Index: ");
    int index = (int) get_unum();

    if (index % 3 == 0)
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    if (number < 3070230528 || number >= 3087007744) // number starts with 0xb7
        numbers[index] = number;
    else
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    return 0;
}

int read_number(int *numbers)
{
    printf(" Index: ");
    int index = (int) get_unum();
    printf(" Number at data[%u] is %u\n", index, numbers[index]);
    return 0;
}

int main(int argc, char **argv, char **envp)
{
    int n1 = 0;
    char cmd[20] = {0};
    
    int numbers[404] = {0};
    bzero(numbers, 100);

    if (argv[0] != NULL)
        memset(argv[0], 0, strlen(argv[0]));
    if (envp[0] != NULL)
        memset(envp[0], 0, strlen(envp[0]));
    // actually whole envp and argv are cleared

    puts("----------------------------------------------------");

    while (1)
    {
        printf("Input command: ");
        n1 = 1;
        fgets(cmd, 20, stdin);
        cmd[strlen(cmd) - 1] = '\0';

        int res;
        if (strncmp(cmd, "store", 5) == 0)
            res = store_number(numbers);
        else if (strncmp(cmd, "read", 4) == 0)
            res = read_number(numbers);
        else if (strncmp(cmd, "quit", 4) == 0)
            break;

        if (res != 0)
            printf(" Failed to do %s command\n", cmd);
        else
            printf(" Completed %s command successfully\n", cmd);

        bzero(cmd, 20);
    }

    return 0;
}