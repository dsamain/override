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
        cmp al, 0x40
        jle suce2
    */
    if (buf[pouet] <= 0x40)
        goto suce2;
    
    /*
        mov eax, buf
        add eax, pouet
        movzx eax, byte ptr [eax]
        cmp al, 0x5a
        jg suce2
    */
    if (buf[pouet] > 0x5a)
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
        https://stackoverflow.com/questions/26783797/repnz-scas-assembly-instruction-specifics

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
    const char *p = buf;
    while (*p++ != '\0')
        pouet2--;
    pouet2 = ~pouet2 - 1;
    if (pouet2 < 0x1f)
        goto suce1;

    printf(buf);
    exit(0);
}


// V2
int main()
{
    char buf[100]; // esp+0x28

    fgets(buf, 100, stdin);

    for (int i = 0; strlen(buf) < 0x1f; i++)
    {
        // if (buf[i] <= 0x40)
        //     continue;
        // if (buf[i] > 0x5a)
        //     continue;
        // buf[i] ^= 0x20; // = lowercasify

        if (buf[i] < 'A' || buf[i] > 'Z')
            continue;

        buf[i] += 0x20; // = lowercasify
    }
    
    printf(buf);
    exit(0);
}