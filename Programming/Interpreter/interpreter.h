#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "./input_stream.bin"

#define END 0x00
#define JMP 0x01 // | signed short offset |: Jump execution by the given byte offset.
#define SWP 0x02 // | unsigned byte index | unsigned byte index |: Swap the bytes at given byte indexes.
#define ADD 0x03 // | unsigned byte index | unsigned int adding |: Add a constant unsigned int to the 4 bytes at the given byte index. 
#define XOR 0x04 // | unsigned byte index | long long xoring |: Xor a constant long long to the 8 bytes at the given byte index.
#define INVERT 0x05// | unsigned byte index |: Swap order of bits in the byte at the given byte index.
#define PRINT 0x06 // | ascii char |: Print out the following ascii char.

#define END_SIZE 1
#define JMP_SIZE 3
#define SWP_SIZE 3
#define ADD_SIZE 6
#define XOR_SIZE 10
#define INVERT_SIZE 2
#define PRINT_SIZE 2

