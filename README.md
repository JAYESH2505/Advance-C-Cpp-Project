# Advance-C/C++-Project

**This is a C/C++ project for Advance C/C++ course.**

## Custom Heap Allocator(Memory Allocator)

*Basic Structure*
* Memory Pool Initialization: Set up a fixed-size memory pool.
* Allocate Function: Allocate memory from the pool.
* Free Function: Free allocated memory back to the pool.
*Utility Functions: Additional helper functions as needed.

**In most operating systems, malloc or similar system calls are typically used to request memory from the operating system. If you want to write a custom memory allocator from scratch, you'd still need a way to initially get a large block of memory from the operating system. In Unix-like systems, this is typically done using the brk or sbrk system calls, or more commonly through mmap. Here’s a more detailed example that demonstrates using mmap to allocate a large block of memory and then managing it with a custom allocator.**
    
### Steps=>

Step 1: Set Up the Memory Pool

*A memory pool is a large block of memory reserved in advance, from which smaller chunks can be allocated and deallocated as needed. This helps manage memory more efficiently and reduces the overhead of frequent system calls.*

