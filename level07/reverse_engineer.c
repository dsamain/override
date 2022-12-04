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

int store_number(int *numbers) // ebp +0x8
{
    printf(" Number: ");
    unsigned int number = get_unum(); // ebp-0x10
    printf(" Index: ");
    unsigned int index = get_unum(); // ebp-0xc

    // mov ecx, index
    // mov edx, 0xaaaaaaab
    // mov eax, index

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

   // ecx = index;
   // edx = 0xaaaaaaab;
   // eax = index;

   // eax *= edx;
   // edx = eax >> 0x1f;
   // eax = edx;
   // eax += eax;
   // eax += edx;

   // edx = ecx;
   // edx -= eax;

    // see https://stackoverflow.com/questions/63417818/why-does-division-by-3-require-a-rightshift-and-other-oddities-on-x86
    // int eax = index * 0xaaaaaaab; // 0xaaaaaaab = 2863311531
    // eax >>= 31;
    // eax += eax + eax;
    // if (index - eax == 0)

    // this seems to just be a division, by trying it out, we see that it divides by 3, if remainder is 0, it prints the error
    if (index % 3 == 0)
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    // if (number >> 24 != 0xb7) // if first byte != 0xb7, means the range [0xb7000000, 0xb8000000[ ([3070230528, 3087007744[) is forbidden
    if (number < 3070230528 || number >= 3087007744)
    {
        // mov eax, index
        // shl eax, 2
        // add eax, number
        // mov edx, number
        // mov [eax], edx

        // numbers[index << 2] = number; // numbers[index*4] = number;
        // since numbers is an int array and not char, in bytes we need to mult*4 since sizeof(int) = 4
        numbers[index] = number;
    }
    else
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    return 0;
}

int read_number(int *numbers) // ebp + 0x8
{
    printf(" Index: ");
    unsigned int index = get_unum(); // << 2; // not << 2 since numbers is int array not char anymore
    printf(" Number at data[%u] is %u\n", index, numbers[index]);
    return 0;
}

int main(int argc, char **argv) // argc = esp+0x8, argv = esp+0xc
{
    // add 0x1d0 on stack (464)

    // mov eax, argv (ebp+0x1c)
    // mov esp+0x1c, eax
    char **arguments = argv;

    // mov eax, ebp+0x10
    // mov esp+0x18, eax
    char **arguments2 = (char **)((char *)argv + 2);


    // mov eax,gs:0x14
    // mov esp+0x1cc, eax
    // eax=0
    // these above are probably gcc related to stack protection (canary)

    int n1 = 0; // esp+0x1b4

    // int n2 = 0; // esp+0x1b8
    // int n3 = 0; // esp+0x1bc
    // int n4 = 0; // esp+0x1c0
    // int n5 = 0; // esp+0x1c4
    // int n6 = 0; // esp+0x1c8
    char cmd[20] = {0};
    
    // int pouet;
    // mov eax, &pouet
    // char numbers[100/*(0x64)*/] = {0}; // esp+0x24
    // there seems to be nothing between esp+0x24 and esp+0x1b8 so size is probably 0x1b8-0x24 = 0x194 (404), so 101 ints
    // it's probably 100 in reality but we dont really care
    int numbers[101] = {0};
    // 25 firsts nums (100 first bytes) are set to 0
    bzero(numbers, 100);

    //goto suce2;
//
    //suce1: // main+132
    //memset(argv[0], 0, strlen(arguments[0]));
//
    //suce2: // main+199
    //if (*arguments != NULL)
    //    goto suce1;

    if (arguments[0] != NULL)
        memset(arguments[0], 0, strlen(arguments[0]));

    // main+209 here
    // goto suce3;
    // suce3: // main+278
    // mov eax, *arguments2
    // edx = strlen(arguments2)

    if (arguments[0] != NULL)
        memset(arguments2[0], 0, strlen(arguments[0]));

    // main+288 here
    puts("----------------------------------------------------");

    while (1)
    {
        printf("Input command: ");
        n1 = 1;
        fgets(n2, 20/*(0x14)*/, stdin);

        // mov eax ,strlen(n2)-1
        n2[strlen(n2) - 1] = '\0'; // remove '\n' I guess

        // main+411 here
        // if (strncmp(n2, "read", 5) != 0)
        //     goto suce4;

        // store_number(numbers);

        // suce4: // main+469

        int res;
        if (strncmp(n2, "store", 5) == 0)
            res = store_number(numbers);
        else if (strncmp(n2, "read", 4) == 0)
            res = read_number(numbers);
        else if (strncmp(n2, "quit", 4) == 0)
            break; 

        // main+578 here
        // if (res == 0)
        //     goto suce5;
    // 
        // printf("Failed to do %s command\n", cmd);
        // suce5: // main+614

        if (res != 0)
            printf(" Failed to do %s command\n", cmd);
        else
            printf(" Completed %s command successfully\n", cmd);

        
        // main+638 here
        bzero(cmd, 20); // optimized in asm with 5 ints but same result
        // jmp main+300 (right after puts("--------"")) = while true
    }

    // weird things in asm but I guess it's the stack check
    return 0;
}