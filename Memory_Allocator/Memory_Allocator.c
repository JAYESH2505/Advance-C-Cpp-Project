//* Custom Heap Allocator.

//! Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

//! Pool Size
#define POOL_SIZE (1024 * 1024)

//! Global Variable
static char* memory_pool = NULL;  //? Pointer to the start of the memory pool
static char* free_ptr = NULL;     //? Pointer to the next free block/location in the memory pool
static struct BlockHeader* free_list = NULL; //? Pointer to the head of the free list

//! Adding Metadata (Structure to Store Metadata)
typedef struct BlockHeader {
    size_t size;
    struct BlockHeader* next;
} BlockHeader;

#define BLOCK_HEADER_SIZE sizeof(BlockHeader)

//! Initialize the Memory Pool
void initialize_memory_pool() {
    memory_pool = mmap(NULL, POOL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory_pool == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    free_ptr = memory_pool;
    free_list = NULL;
    printf("Memory pool starts at address: %p\n", (void*)memory_pool);
    printf("Memory pool starts at address (hex): %lx\n", (unsigned long)memory_pool);
}

//! Clean Up the Memory Pool:
void destroy_memory_pool() {
    if (munmap((void*)memory_pool, POOL_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE); // Exit on munmap failure to prevent undefined behavior
    }
    memory_pool = NULL;
    free_ptr = NULL;
    free_list = NULL;
}

//! Function Prototypes:
void* allocate_memory(size_t size);
void free_memory(void* ptr);

int main(int argc, char* argv[]) {
    initialize_memory_pool();

    // Use Memory pool...
    double* a = (double*)allocate_memory(sizeof(double)); // Allocating a double (8 bytes).
    if (a != NULL) {
        *a = 42;
        printf("Memory allocated successfully %f\n", *a);
    } else {
        printf("Failed\n");
    }

    // Free the double
    free_memory(a);

    // Use Memory pool...
    int* b = (int*)allocate_memory(sizeof(int)); // Allocating an int (4 bytes).
    if (b != NULL) {
        *b = 42;
        printf("Memory allocated successfully %d\n", *b);
    } else {
        printf("Failed\n");
    }

    // Free the int
    free_memory(b);

    // Clean up the memory pool
    destroy_memory_pool();
    return 0;
}

//! Implementing the Function
void* allocate_memory(size_t size) {
    BlockHeader* prev = NULL;
    BlockHeader* curr = free_list;

    // Check if there is a suitable block in the free list
    while (curr != NULL) {
        if (curr->size >= size) {
            if (prev == NULL) {
                free_list = curr->next;
            } else {
                prev->next = curr->next;
            }
            return (void*)((char*)curr + BLOCK_HEADER_SIZE);
        }
        prev = curr;
        curr = curr->next;
    }

    // Allocate new block if no suitable block found in the free list
    if (free_ptr + size + BLOCK_HEADER_SIZE > memory_pool + POOL_SIZE) { // Not Enough Memory Left in Pool.
        return NULL;
    }

    BlockHeader* block = (BlockHeader*)free_ptr;
    block->size = size;
    block->next = NULL;

    void* allocated_memory = (void*)(free_ptr + BLOCK_HEADER_SIZE);
    free_ptr += size + BLOCK_HEADER_SIZE;

    return allocated_memory;
}

void free_memory(void* ptr) {
    if (ptr == NULL) return;

    BlockHeader* block = (BlockHeader*)((char*)ptr - BLOCK_HEADER_SIZE);

    // Add block to free list in sorted order
    BlockHeader* prev = NULL;
    BlockHeader* curr = free_list;

    while (curr != NULL && curr < block) {
        prev = curr;
        curr = curr->next;
    }

    // Coalesce adjacent blocks
    if (prev != NULL && (char*)prev + BLOCK_HEADER_SIZE + prev->size == (char*)block) {
        prev->size += BLOCK_HEADER_SIZE + block->size;
        block = prev;
    } else {
        block->next = curr;
        if (prev != NULL) {
            prev->next = block;
        } else {
            free_list = block;
        }
    }

    if (curr != NULL && (char*)block + BLOCK_HEADER_SIZE + block->size == (char*)curr) {
        block->size += BLOCK_HEADER_SIZE + curr->size;
        block->next = curr->next;
    }
}
