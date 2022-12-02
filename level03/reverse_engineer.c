void decrypt(int arg)
{
    // compare 'Congratulations!' with something, if equal, /bin/sh

}

void test(int arg1, int arg2) // arg1 = scanf("%d"), argv = 0x1337d00d
{
    arg2 -= arg1; // 0x1337d00d - scanf("%d")
    if (arg2 > 21)
    {
        rand();
        decrypt();
    }
    else
    {
        arg2 = arg2 << 2;
        arg2 += 0x80489f0;
        // the max we can have is 84 (21 << 2) + 0x80489f0 = 0x8048a44
        // min is 0x80489f0, we can see it's in .rodata, and it's binary values, how lucky
        // so jmp range is [0x80489f0, 0x8048a44]

        // basically here is the jmp table:
        /*
            Values (start at 0x80489f0, end at 0x8048a44 included): (in little endian)
            4a880408
            75870408

            85870408
            95870408
            a5870408
            b5870408

            c5870408
            d5870408
            e2870408
            ef870408

            4a880408
            4a880408
            4a880408
            4a880408

            4a880408
            4a880408
            fc870408
            09880408

            16880408
            23880408
            30880408
            3d880408

        */
        // 0x080489f0 -> 0x0804884a ( decrypt(rand()) ) (input = 322424845)
        // 0x080489f4 -> 0x08048775 ( decrypt(arg2) ) 

        // 0x080489f8 -> 0x08048785 ( decrypt(arg2) )
        // 0x080489fc -> 0x08048795 ( decrypt(arg2) )
        // 0x08048a00 -> 0x080487a5 ( decrypt(arg2) )
        // 0x08048a04 -> 0x080487b5 ( decrypt(arg2) )

        // 0x08048a08 -> 0x080487c5 ( decrypt(arg2) )
        // 0x08048a0c -> 0x080487d5 ( decrypt(arg2) )
        // 0x08048a10 -> 0x080487e2 ( decrypt(arg2) )
        // 0x08048a14 -> 0x080487ef ( decrypt(arg2) )

        // 0x08048a18 -> 0x0804884a ( decrypt(rand()) )
        // 0x08048a1c -> 0x0804884a ( decrypt(rand()) )
        // 0x08048a20 -> 0x0804884a ( decrypt(rand()) )
        // 0x08048a24 -> 0x0804884a ( decrypt(rand()) )

        // 0x08048a28 -> 0x0804884a ( decrypt(rand()) )
        // 0x08048a2c -> 0x0804884a ( decrypt(rand()) )
        // 0x08048a30 -> 0x080487fc ( decrypt(arg2) )
        // 0x08048a34 -> 0x08048809 ( decrypt(arg2) )

        // 0x08048a38 -> 0x08048816 ( decrypt(arg2) )
        // 0x08048a3c -> 0x08048823 ( decrypt(arg2) )
        // 0x08048a40 -> 0x08048830 ( decrypt(arg2) )
        // 0x08048a44 -> 0x0804883d ( decrypt(arg2) )


        // jmp *pouet

        // simplest solution we can think of is just trying them all (except the rand() ones)
        // and see which one works

        // so we need to try:
        // 0x1337d00d - 1 to 0x1337d00d - 9
        // 0x1337d00d - 16 to 0x1337d00d - 21

        // in decimal:
        // 322424844 to 322424835
        // 322424828 to 322424823
    }


}

int main()
{
    srand(time());

    int arg1;
    scanf("%d", &arg1);

    test(arg1, 0x1337d00d);
}