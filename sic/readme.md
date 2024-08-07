# SIC Assembler

## Overview

This directory contains the source code and example programs for a SIC (Simplified Instructional Computer) assembler. The assembler reads SIC assembly code, generates symbol tables, and produces an object program.

## Directory Structure

- `Program1.asm`: Example SIC assembly program.
- `Program2.asm`: Another example SIC assembly program.
- `sicAssembly.c`: C program for assembling SIC assembly code.
- `OPTable.instr`: Instruction set for the SIC assembler.

## How It Works

### SIC Assembly Programs

The SIC assembly programs (`Program1.asm` and `Program2.asm`) contain instructions written in SIC assembly language. These programs are used as input to the assembler.

#### Example Code Snippet from `Program1.asm`

```assembly:sic/Program1.asm
startLine: 1
endLine: 19
```

### SIC Assembler

The assembler (`sicAssembly.c`) reads the assembly code, generates symbol tables, and produces an object program. It consists of two main passes:

1. **PASS1**: Reads the source file, generates the symbol table, and creates an intermediate file.
2. **PASS2**: Reads the intermediate file, generates the object code, and writes the object program.

#### Example Code Snippet from `sicAssembly.c`

```c:sic/sicAssembly.c
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int PASS1(const char *programFileName);
int PASS2();
void cleanFiles();

int main(int argc, char *argv[])
{
    const char *programFileName;

    if (argc >= 2)
    {
        programFileName = argv[1];
    }
    else
    {
        printf("\nUsage: %s <program_file> (Using Default \"Program1.asm\")\n", argv[0]);
        programFileName = "Program1.asm";
    }

    PASS1(programFileName);

    PASS2();

    if (argc == 3 && strcmp(argv[2], "--clean") == 0)
    {
        cleanFiles();
    }

    return 0;
}
```

### Instruction Set

The instruction set (`OPTable.instr`) contains the opcodes for the SIC assembler. This file is used by the assembler to look up the opcodes for the instructions in the assembly programs.

#### Example Code Snippet from `OPTable.instr`

```plaintext:sic/OPTable.instr
startLine: 1
endLine: 25
```

## Running the Assembler

1. **Compile the SIC Assembler:**
   ```sh
   gcc sicAssembly.c -o SICAssembler
   ```

2. **Run the SIC Assembler:**
   ```sh
   ./SICAssembler Program1.asm
   ```

3. **Clean Up Generated Files (Optional):**
   ```sh
   ./SICAssembler Program1.asm --clean
   ```

## Conclusion

This directory provides a simple yet comprehensive example of a SIC assembler. It includes example SIC assembly programs, the assembler source code, and the instruction set. By following the steps above, you can compile and run the assembler to generate object programs from SIC assembly code.
