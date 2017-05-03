#include <stdint.h>

#ifndef __KERNEL_PAGING_H__
#define __KERNEL_PAGING_H__

namespace kernel {
    namespace memory {
        //http://wiki.osdev.org/Paging
        class page {
        private:
            
        public:
            class directory {
                
            };
            //Maps a physical address to a virtual address
            static void map(void* physical_address, void* virtual_address, int flags);
            //Translates a virtual address to the actual physical address
            static void* get_physical_address(void* virtual_address);
        };
    }
}

#endif /* __KERNEL_PAGING_H__ */

