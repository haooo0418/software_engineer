#!/bin/bash
# Script to compile and run AFL++ fuzzing

# Compile with AFL++
echo "Compiling with afl-clang-fast..."
afl-clang-fast -o fuzz_target fuzz_target.c

# Create input and output directories
mkdir -p fuzz_input fuzz_output

# Create initial test cases
echo "ADD:5,3" > fuzz_input/test1.txt
echo "CALC:10+5" > fuzz_input/test2.txt
echo "REPEAT:3,hello" > fuzz_input/test3.txt
echo "MAGIC:test" > fuzz_input/test4.txt

echo "Setup complete. To run fuzzing, execute:"
echo "afl-fuzz -i fuzz_input -o fuzz_output ./fuzz_target @@"
