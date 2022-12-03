#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void clear_stdin()
{
    char c = 0; // ebp-0x9
    
    // c = getchar();
    // while (c != EOF) // (c != 0xff, so we guess EOF since it's -1 and function name is clear_stdin)
    //     c = getchar();

    while (getchar() != EOF); // same as above, just shorter

    return;
}

unsigned int get_unum()
{
    int unum = 0; // ebp-0xc
    fflush(stdout);

    scanf("%u", &unum);
    clear_stdin();
    return unum;
}

void store_number(int *number, int index)
{
    // 0x28 on stack
    printf(" Number: ");
    unsigned int unum1 = get_unum(); // ebp-0x10
    printf(" Index: ");
    unsigned int unum2 = get_unum(); // ebp-0xc

    // mov ecx, unum2
    // mov edx, 0xaaaaaaab
    // mov eax, unum2

    // mul edx
    // shr edx, 0x1f
    // mov eax, edx
    // add eax, eax
    // add eax, edx

    // mov edx, ecx
    // sub edx, eax
    // test edx, edx


   // int ecx;
   // int edx;
   // int eax;

   // ecx = unum2;
   // edx = 0xaaaaaaab;
   // eax = unum2;

   // eax *= edx;
   // edx = eax >> 0x1f;
   // eax = edx;
   // eax += eax;
   // eax += edx;

   // edx = ecx;
   // edx -= eax;


    int eax = unum2 * 0xaaaaaaab;
    eax >>= 31;
    eax += eax + eax;
    if (unum2 - eax == 0)
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    if (unum1 >> 24 != 0xb7)
    {
        // mov eax, unum2
        // shl eax, 2
        // add eax, number
        // mov edx, unum1
        // mov [eax], edx

        number[unum2 >> 2] = unum1;
    }
    
    return 0;
}