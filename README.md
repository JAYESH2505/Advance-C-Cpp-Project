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



Step 2: Implement a Simple Allocation Function

* Define the Allocation Function:
We'll define a function allocate_memory that takes a size and returns a pointer to the allocated memory block.

* Check for Sufficient Memory:
The function needs to ensure there is enough memory left in the pool to fulfill the allocation request.

* Return the Allocated Memory:
The function will return a pointer to the start of the allocated memory block and update the free_ptr to the next free location.*

Step 3: Implement a Simple Free Function

* Define the Free Function:
We'll define a function free_memory that takes a pointer to the memory block to be freed.

* Add Metadata:
To manage memory blocks efficiently, we need to add some metadata to each allocated block. This metadata will include the size of the block, which will help in merging free blocks later.

* Update the Free Function:
The free_memory function will mark the block as free and, for simplicity, we'll assume it can merge contiguous free blocks (though a more advanced allocator would handle this more robustly).

Step 4: Implementing Coalescing and Enhancing Error Handling
Objective:

* Implement coalescing of adjacent free blocks to reduce fragmentation.
* Add error handling for scenarios like double-free and invalid free.
