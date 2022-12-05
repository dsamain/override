#include <stdio.h>

void log_wrapper(FILE *file, char *s, char *t) {
    // file = fopen("./backups/.log", "w");
    // s = "starting backup:"
    // t = av[1]

    //sub    rsp,0x130
    //mov    QWORD PTR [rbp-0x118],rdi
    //mov    QWORD PTR [rbp-0x120],rsi
    //mov    QWORD PTR [rbp-0x128],rdx
    // file: [rbp - 0x118]
    // s: [rbp - 0x120]
    // t: [rbp - 0x128]

    //mov    rax,QWORD PTR fs:0x28
    //mov    QWORD PTR [rbp-0x8],rax
    int pouet = 0x28; // [rbp - 0x8]
    // rdx = [rbp-0x120]
    // rax = rbp-0x110
    // rsi = rdx
    // rdi = rax
    // call strcpy
    char buf[0x110]; // rax = [rbp - 0x110]
    strcpy(buf, s);
    // rsi = [rbp-0x118] (file)
    // [rbp-0x130] = 0xfffffffffff
    int pouet2 = 0xffffffffff;
    // rdx = rax (buf)
    // rcx = pouet2
    // rdi = rdx (buf)
    // 115
    //repnz scas al,BYTE PTR es:[rdi]
    int sz = strlen(buf); // <- pas sur de ca
    // rdx = sz-1;
    // eax = 0xfe
    // r8 = rax
    // r8 -= rdx 
    // rax = buf
    // 145
    // pouet2 = 0xffffffffff



}

int main(int ac, char **av) {
    // ac: rbp-0x94
    // av: rbp-0xa0
    // [rbp-0x8] = 0x28
    // [rbp-0x71] = 0xff
    // [rbp-0x78] = 0xfffffffff

    //cmp    DWORD PTR [rbp-0x94],0x2
    //je     0x400a4a <main+90>

    int ret = 0;
    if (ac != 2) {
        // rax = av
        // rdx = av[0] ([rax])
        // eax = 0x400a4a ("usage...")
        // rsi = av[0] (rdx)
        // rdi = av (rax)
        // eax = 0;
        printf("Usage: ./level08 filename");
    }
    // edx = "w"
    // eax =  "./backups/.log"
    // rsi = rdx
    // rdi = rax
    FILE *ret = fopen("./backups/.log", "w");
    if (ret == 0) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }
    // 161

    //rax,QWORD PTR [rbp-0xa0]
    //add    rax,0x8
    //mov    rdx,QWORD PTR [rax]
    char *str = av[1]; // (rdx)
    // esi = "startin backup"
    // rdi = rax
    log_wrapper(ret, "Starting back up: ", av[1]);
    // 195
    // edx = "r"
    // rax = av[1]
    // rsi = rdx ("r")
    // rdi = rax (av[1])
    ret = fopen(av[1], "r");
    if (ret == 0) {
        printf("ERROR: Failed to open %s\n", av[1]);
        exit(1);
    }
    // 281
    // edx = "./backups/"
    char *tmp = "./backups/";
    // rax = rbp-0x70
    char buf2[0x70]; // [rbp-0x70]
    // [rbp-0xa8] = 0xfffffffff 
    // rdx = rax
    // rcx = 0xffffffff
    // rdi = rdx
    // repnz scas al,BYTE PTR es:[rdi]
    //strchr(file, '/');
}