#include <kernel/multiboot_info.h>

//This manages the PHYSICAL memory only. Use paging to allocate virtual memory.

#ifndef MEMMAN_H
#define MEMMAN_H

namespace kernel {
    namespace memory {
        namespace manager {
            //Initializes the memory table with the initial multiboot memory map
            void init(multiboot& mb);
            
            //Allocates a block of memory starting from 'start' for size 'size'
            //Returns 'start' if successful or else a null pointer
            void* reserve(void* start, uint32_t size);
            
            //Frees the given block of memory (marks it available)
            void free(void* block);
        }
    }
}

#endif /* MEMMAN_H */

