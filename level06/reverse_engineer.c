#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int serial) // login = ebp+0x8, serial = ebp+0xc
{
//     size_t size = strcspn(login, "\n");
//     login[size] = '\0';
    login[strcspn(login, "\n")] = '\0';

    int pouet = strnlen(login, 32); // ebp-0xc

    // push eax
    // xor eax, eax
    // je
    // weird thing
    // pop eax

    if (pouet <= 5)
        return (1);

    // ptrace(0, 0, 1, 0);
    // ptrace(PTRACE_TRACEME, 0, 1, 0);

    // probably if gdb, then fuck you
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
    {
        puts(".[32m.---------------------------.");
        puts("| !! TAMPERING DETECTED !!  |");
        puts(".[32m'---------------------------'");
        return (1);
    }

    /*
        mov    eax,DWORD PTR [ebp+0x8]
        add    eax,0x3
        movzx  eax,BYTE PTR [eax]
        movsx  eax,al
        xor    eax,0x1337
        add    eax,0x5eeded
        mov    DWORD PTR [ebp-0x10],eax
        mov    DWORD PTR [ebp-0x14],0x0
    */

    int c = (int)login[3];
    c = c ^ 0x1337;
    c = c + 0x5eeded;

    int p1 = c; // ebp-0x10
    int p2 = 0; // ebp-0x14
    goto suce1;

    suce2:
    if (login[p2] > 0x1f)
        goto suce3;

    return 1;

    suce3:
    // mov eax, p2
    // add eax, login
    // movzx eax, BYTE PTR [eax]
    // movsx eax, al

    // mov ecx, eax
    // xor ecx, p1
    // mov edx, 0x88233b2b
    // mov eax, ecx
    // mul edx // mul dest operand is implicit: edx (or ax if operand is 16 bits or less)
    // mov eax, ecx
    // sub eax, edx
    // shr eax, 1
    // add eax, edx
    // shr eax, 0xa
    // imul eax, eax, 0x539
    // mov edx, ecx
    // sub edx, eax
    // mov eax, edx
    // p1 += eax
    // p2 += 1

    int eax;
    int ecx;
    int edx;

    eax = login[p2];
    ecx = eax;
    ecx = ecx ^ p1;
    eax = ecx;
    edx = 0x88233b2b * eax;
    eax = ecx;
    eax = eax - edx;
    eax = eax >> 1;
    eax = eax + edx;
    eax = eax >> 10;
    eax = eax * 0x539;
    edx = ecx;
    edx = edx - eax;
    eax = edx;
    
    p1 += eax;
    p2 += 1;




    suce1:
    if (p2 < pouet)
        goto suce2;

    if (serial == p1)
        return (0);

    return 1;
}

int main()
{
    puts("***********************************");
    puts("*		level06		  *");
    puts("***********************************");
    printf("-> Enter Login: ");

    char login[32 /*(0x20)*/]; // esp + 0x2c
    fgets(login, 32, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");

    unsigned int serial; // esp + 0x28
    scanf("%u", &serial);

    if (auth(login ,serial) == 0)
    {
        puts("Authenticated!");
        system("/bin/sh");
        return (0);
    }
}