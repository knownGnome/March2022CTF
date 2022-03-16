# Graph Search Programming Challenge 
## Overview
Write a graph search algorithm which will open the file `input_stream.bin`, load in a graph which has been serialized, and search for a specific node in the graph. The flag can be printed out using the secondary data fields of the nodes along the path to the destination node. 

Note: Being able to do this in C is good practice for the interview.

## Instructions
### Reading the Graph
You have been provided the binary file, `input_stream.bin`. This file contains a graph which has been serialized (meaning transferred into raw binary data).

Each graph node takes the following form:
```
| Val |  Length   |    Out    |    Out    | ... |
|  0  |  1  |  2  |  3  |  4  |  5  |  6  | ... |
```

Val: The ASCII value stored by the node.
Length: The number of Out links.
Out: Represents a one-directional link from this node to another. Out refers to the destination node by index within the binary file.

The first node in the graph will begin at the start of the binary file (offset 0). The target node will have a val of '}'.

### Printing the Flag
Get the flag by printing out the ASCII character represented by each node's val on the shortest path to the last node.

Example of a graph:
```
|'h'|2|3|2|
|'}'|2|0|2|
|'e'|1|4|
|'i'|2|1|0|
|'y'|3|1|0|2|
```

The shortest path from the start to '}' is made of up the values which form the flag: "hi}"

## Scoring
As always when preparing your writeup, you will be evaluated based on the following software engineering pillars:

- Correctness (printing the flag)
- Safe from bugs (handles bad input without crashing)
- Easy to understand (commented and inuitive program structure)
- Ready for change (modular implementation)
- Adherence to the [Google C Style Guide](https://google.github.io/styleguide/cppguide.html).
