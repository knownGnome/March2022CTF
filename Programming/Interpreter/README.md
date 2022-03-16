# Interpreter Programming Challenge 


## Overview
Write an interpreter which will open the file `input_stream.bin` and execute the instructions encoded within. A successful interpreter will print out the flag.


## Instructions
See the header file `interpreter.h` for opcodes.

### END
End of program


### JMP 
Jump execution by the given byte offset.

`| OPCODE | signed short offset |` (3 bytes)

### SWP 
Swap the bytes at given byte indexes.

`| OPCODE | unsigned byte index | unsigned byte index |` (3 bytes)

### ADD
Add a constant unsigned int to the 4 bytes at the given byte index. 

`| OPCODE | unsigned byte index | unsigned int adding |` (6 bytes)

### XOR 
Xor a constant long long to the 8 bytes at the given byte index.

`| OPCODE | unsigned byte index | long long xoring |` (10 bytes)

### INVERT
Swap order of bits in the byte at the given byte index.

`| OPCODE | unsigned byte index |` (2 bytes)

### PRINT
Print out the following ascii char.

`| OPCODE | ascii char |` (2 bytes)


## Scoring
You will be evaluated based on the following software engineering pillars:

- Correctness (printing the flag)
- Safe from bugs (handles bad input without crashing)
- Easy to understand (commented and inuitive program structure)
- Ready for change (modular implementation)
- Adherence to the [Google C Style Guide](https://google.github.io/styleguide/cppguide.html).
