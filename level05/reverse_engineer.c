#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char buf[100]; // esp+0x28
    int pouet = 0; // esp+0x8c
    int pouet2 = 0xffffffff; // esp+0x1c

    fgets(buf, 100, stdin);

    goto suce3;

// if comment in /**/ in means its already translated into c code
// registers: https://flint.cs.yale.edu/cs421/papers/x86-asm/x86-registers.png
    suce1:
    /*
        mov eax, buf
        add eax, pouet
        movzx eax, byte ptr [eax]
        cmp al, 0x40 (64)
        jle suce2
    */
    if (buf[pouet] <= 0x40)
        goto suce2;
    
    /*
        mov eax, buf
        add eax, pouet
        movzx eax, byte ptr [eax]
        cmp al, 0x5f (95)
        jg suce2
    */
    if (buf[pouet] > 0x5f)
        goto suce2;

    /*
        mov eax, buf
        add eax, pouet
        movzx eax, byte ptr [eax]
        mov edx, eax
        xor edx, 0x20 (32)
        mov eax, buf
        add eax, pouet
        mov byte ptr [eax], dl
    */
    buf[pouet] ^= 0x20;
    

    suce2:
    pouet += 1; // add pouet, 1

    suce3:
    pouet2 = 0xffffffff;

    /*
        mov edx, buf
        mov eax, 0
        mov ecx, pouet2
        mov edi, edx
        repnz scas al, byte ptr es:[edi]
        mov eax, ecx
        not eax
        sub eax, 1
        cmp eax, 0x1f
        jb suce1
    */
    if (strlen(buf) <= 0x1f) // copilot did this one so i hope its right
        goto suce1;

    printf(buf);
    exit(0);
}