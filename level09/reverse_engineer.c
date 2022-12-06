// First six arguments are in rdi, rsi, rdx, rcx, r8d, r9d; remaining arguments are on the stack.
// https://wiki.cdot.senecacollege.ca/wiki/X86_64_Register_and_Instruction_Quick_Start

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void secret_backdoor()
{
    // https://stackoverflow.com/questions/71061184/understanding-x86-64-assembly-for-simple-program-in-c-with-a-function-call
    
    char buf[128 /*(0x80)*/];
    system(fgets(buf, 128, stdin)); // we guess stdin
}


void handle_msg()
{
    // sub rsp, 0xc0
    // lea rax, [rbp-0xc0]
    // add rax, 0x8c

    // buf = rbp-0xc0 + 0x8c = rbp-0x34
    char buf[40] = {0}; // we see it sets eax, eax+8, eax+0x10, eax+0x18 and eax+0x20 to 0, so probably faster init than memset since buf is small

    int pouet = 0x8c; // rbp0xc

    set_username(rsp);
    set_msg(rsp);

    // its written addr 0x555555554bc0
    // but idk since its 64 bit we guess its 0x00000bc0 in .rodata which is the string below
    puts(">: Msg sent!");
}


// void set_username(char *arg)
// {
//     // sub rsp, 0xa0
//     // mov [rbp-0x98], rdi (arg)

//     // rep stos of QWORD for 0x10 (16) times
//     char buf[0x80] = {0}; // rbp-0x90
//     puts(">: Enter your username");
//     printf(">>: ");
//     fgets(buf, 0x80, stdin); // we guess stdin

//     // movv [rbp-0x4], 0x0
//     int pouet = 0;
//     goto suce1;

//     suce0: // set_username+121
//     // mov eax, pouet
//     // cdqe
//     // movzvx ecx, BYTE PTR [rbp-0x90+rax]
//     // mov rdx, arg
//     // movv eax, pouet
//     // cdqe
//     // mov BYTE PTR [rdx+rax+0x8c], cl
//     // add pouet, 0x1

//     ecx = buf[pouet];
//     rdx = arg;
//     arg[pouet + 0x8c] = buf[pouet];
//     pouet++;


//     suce1: // set_username+157
//     // cmp [rbp+0x4], 0x28
//     if (pouet > 40)
//         goto suce2;

//     // cdqe
//     // movzx eax, BYTE PTR [rbp+rax-0x90]
//     // test al, al
//     if (buf[pouet] != 0)
//         goto suce0;

//     suce2: // set_username+180
//     printf(">: Welcome, %s", arg + 0x8c);
// }


// V2 with loop
void set_username(char *arg)
{
    char buf[128] = {0};
    puts(">: Enter your username");
    printf(">>: ");
    fgets(buf, 128, stdin);

    for (int i = 0; i <= 40; i++)
    {
        if (buf[i] == '\0')
            break;

        arg[i + 140 /*(0x8c)*/] = buf[i];
    }

    printf(">: Welcome, %s", arg + 0x8c);
}


void set_msg(char *arg) // arg = rbp-0x408
{
    // sub rsp, 0x410
    char buf[1024] = {0}; // rbp-0x400
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    
    fgets(buf, 1024, stdin); // we guess stdin
    strncpy(arg, buf, arg[180 /*(0xb4)*/]);
}

int main()
{
    puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~   v1337|\n--------------------------------------------");
    handle_msg();
    return 0;
}