# Data_Structures

## Detailed description
A collection of data structures implemented in C from scratch, with a
focus on hands on learning and understanding how they work internally.
This project was written to practice low level programming, memory
management, pointers manipulation and the implementation of the
fundamental data structures from scratch without relying on external
libraries.

## Features

### Currently implemented
- **Dynamic Array**
- **Queue**
- **Stack**
- **Hash Table**
- **Linked List**
- **Binary Search Tree**
- **Heap**
- **Graph (adjacency list)**

### Algorithms
A separate `Algorithms/` folder contains utility functions that combine multiple data structures to solve common algorithmic problems.

### Testing

Every data structure includes tests covering:

- Basic operations
- Edge cases
- Randomized stress tests
- Duplicate handling (when supported)

Run a test:

```
gcc tests/Heap_test.c -L. -lds -o heap_test
./heap_test
```

## Planned implementations
- **Graph (adjacency matrix)**
- **AVL tree**
- **Breadth first search**
- **Depth first search**
- **Dijkstra**

## Project structure

Each data structure lives in its own folder with three files:

- `name.h` — public interface: struct definitions and function
  declarations. This is the file you `#include` to use the structure.
- `name.c` — implementation of every function declared in the header.
- `README.md` — explanation of the structure, its operations, and the
  design decisions made while building it.

A `ds.h` file at the root includes every structure's header, so a user
can just write `#include "ds.h"` to access everything in the library.

A `Makefile` at the root automates compilation: it compiles every
structure's `.c` file into an object file (`.o`), then bundles all of
them into a single static library, `libds.a`, using `ar`. This means a
user never has to manually list every source file when compiling — they
just run `make` (or `mingw32-make` on Windows) once, and link against
`libds.a`.

```
Data_Structures/
├── Makefile        
├── ds.h
├── Algorithms/
│   ├── algorithms.c
│   ├── algorithms.h
│   └── README.md
├── tests/
│   ├── Heap_test.c
│   └── Dynamic_array_test.c
├── Stack/
│   ├── stack.c
│   ├── stack.h
│   └── README.md
├── Queue/
│   ├── Queue.c
│   ├── Queue.h
│   └── README.md
├── Array/
│   ├── dynamic_array.c
│   ├── dynamic_array.h
│   └── README.md
├── Hash_Table/
│   ├── hash_table.c
│   ├── hash_table.h
│   └── README.md
├── Heap/
│   ├── Heap.c
│   ├── Heap.h
│   └── README.md
├── Graph/
│   ├── Graph.c
│   ├── Graph.h
│   ├── Hash_Table_Graph.c
│   ├── Hash_Table_Graph.h
│   └── README.md
└── Linked_List/
    ├── linked_list.c
    ├── linked_list.h
    └── README.md
```

## Installation

Clone the repository:

```bash
git clone https://github.com/ali-hue-byte/Data_Structures.git
cd Data_Structures
```

Build the static library:

```bash
mingw32-make    # Windows (MSYS2 / MinGW)
make            # Linux / macOS
```

This compiles every structure into object files and bundles them into
`libds.a`. To use the library in your own project, link against it:

```bash
gcc your_program.c -I/path/to/Data_Structures -L/path/to/Data_Structures -lds -o your_program
```

For example, if both folder (Data_structures) and your program (test.c) are in Desktop :

```bash
cd Desktop
gcc test.c -I./Data_Structures -L./Data_Structures -lds -o test
```

Then run it :

```bash
test        # Windows
./test      # Linux / macOS
```


In your code:

```c
#include "path/to/ds.h"
```

To remove the compiled object files and the library:

```bash
mingw32-make clean
make clean
```

## Example

```c
#include "ds.h"
#include <stdio.h>

int main(){
    Stack s;
    s.top = NULL;

    stack_push(&s, 10);
    stack_push(&s, 20);
    print_stack(&s); // 20 10

    Hash_Table h = create_hash_table();
    Hash_Table_add(&h, "score", 100);
    printf("%d\n", Hash_Table_get(&h, "score")); // 100

    return 0;
}
```

