// Step 1
/*
Set up a Memory Pool
*/


//! Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

//! Pool Size
#define POOL_SIZE (1024*1024)

//! Global Variable
static char* memory_pool=NULL;  //? Pointer to the start of the  memory pool
static char* free_ptr=NULL;     //? Pointer to the  next free block/location in the memory pool

//! Initialize the Memory Pool
void initialize_memory_pool() {
    memory_pool = mmap(NULL, POOL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory_pool == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    free_ptr = memory_pool;
}

//! Clean Up the Memory Pool:
void destroy_memory_pool(){
    if(mumup(memory_pool,POOL_SIZE)==-1)
        perror("mumup")
    
    memory_pool=NULL;
    free_ptr=NULL;
}




int main(int args,char* argv){
    initialize_memory_pool()

    //use Memory pool...

    destroy_memory_pool();
    return 0;
}