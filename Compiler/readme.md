# C Compiler for While Loops

This directory contains the implementation of a simple C compiler focusing on while loops. The compiler is designed to translate C code with while loops into assembly language.

## Components

1. **Lexer**: Breaks down the input C code into tokens.
2. **Parser**: Analyzes the structure of the code and builds an Abstract Syntax Tree (AST).
3. **Code Generator**: Converts the AST into assembly code.

## How it Works

1. The compiler reads the input C file containing while loops.
2. The lexer tokenizes the input, identifying keywords, identifiers, and symbols.
3. The parser constructs an AST, representing the structure of the while loop and its body.

## Usage

To compile a C file with while loops:

1. Place your C source file in the input directory.
2. Run the compiler: `./compiler input/your_file.c`
3. The resulting assembly code will be in the output directory.

## How to Run

To execute specific phases of the compiler:

- Navigate to the relevant directory (e.g., `01Lexical/`, `02SyntaxTree/`, or `03LRParser/`).
- Compile and run the corresponding source file (e.g., `lexical.cpp`, `SyntaxPhase.cpp`, or `shiftreduce.cpp`).

For example:

```bash
cd Compiler/01Lexical/
g++ lexical.cpp -o lexicalAnalyzer
./lexicalAnalyzer
```

## Dependencies

- C++ compiler for compiling the source files.
- Input files such as `input.c`, `While.c`, and `rules.txt` as required by specific phases.
