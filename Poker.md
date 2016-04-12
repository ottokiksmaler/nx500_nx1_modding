# poker - tool for read/write access to another process' memory

Access memory of another process 4 bytes at a time

Source is here: https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/poker.c

Compiled binary is here: https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/poker

Usage: ./poker <PID> <hex_address[:hexpair_value[:hexpair_value_original]]>

Example:
./poker 247 0x00400658 - reads 4 bytes from address 0x00400658 of PID 247

Example:
./poker 247 0x00400658:45464748 - changes 4 bytes to 'EFGH' at address 0x00400658' of PID 247

Example:
./poker 247 0x00400658:45464748:42424242 - changes 'AAAA' to 'EFGH' at address 0x00400658' of PID 247 only if original bytes were 'AAAA'

./poker 247 0x00400658:45464748:42424242 0x00400668:45464748 0x00800658:45464748 0x00400444:45464748:41414141- works as well

FWIW - you can compile this on x86 and use it for the same thing (see source for how to use it for different needs).
