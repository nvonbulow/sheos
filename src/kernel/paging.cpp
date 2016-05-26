#include <kernel/paging.h>

inline void set_page_directory_address(void* addr) {
	
}

namespace kernel {
	namespace memory {

		void* page::get_physical_address(void* virtual_address) {
			//to be implemented
		}

		void page::map(void* physical_address, void* virtual_address, int flags) {
			//Don't forget to flush the tlb!!
		}
	}
}