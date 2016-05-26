#include <kernel/gdt.h>
#include <kernel/asm.h>
#include <stdint.h>
#include <stddef.h>
#include <kernel/bits.h>

static uint64_t entry_table[8192];

static inline void _lgdt(void* table) {
    asm volatile(
                 "lgdt %0" : :
                 "m"(table)
    );
}

namespace kernel {
	namespace memory {
		
		gdt_entry::gdt_entry() {
			entry = 0;
			//Clear the low two bits in flags and set to only 32 bit protected
			entry = set_bits(entry, 52 + 0, 3, 0x00);
			//Set the unused and present bits
			entry = set_bits(entry, 40 + 4, 1, 1);
			entry = set_bits(entry, 40 + 7, 1, 1);
		}
		gdt_entry::gdt_entry(gdt_entry& value) {
			entry = value.entry;
		}

		
		void gdt_entry::set_base_address(void* address) {
			uintptr_t addr = (uintptr_t) address;
			uint64_t addr_low = get_bits(addr, 0, 24);
			uint64_t addr_high = get_bits(addr, 24, 8);
			
			//Low 24 bits of address start at bit 16
			entry = set_bits(entry, 16, 24, addr_low);
			//High 8 bits of address start at bit 56
			entry = set_bits(entry, 56, 8, addr_high);
		}
		void* gdt_entry::get_base_address() {
			uint64_t addr = 0;
			//Low 24 bits
			addr |= get_bits(entry, 16, 24);
			addr |= get_bits(entry, 56, 8) << 24;
			return (void*) (addr & bit_mask(32));
		}
		
		void gdt_entry::set_limit_address(void* address) {
			//This is a 20 bit address
			uintptr_t addr = (uintptr_t) address;
			//Low 16 bits
			uint64_t addr_low = get_bits(addr, 0, 16);
			//High 4 bits
			uint64_t addr_high = get_bits(addr, 16, 4);
			entry = set_bits(entry, 0, 16, addr_low);
			entry = set_bits(entry, 48, 4, addr_high);
		}
		void* gdt_entry::get_limit_address() {
			uint64_t addr = 0;
			addr |= get_bits(entry, 0, 16);
			addr |= get_bits(entry, 48, 4);
			return (void*) addr;
		}
		
		void gdt_entry::set_privilege_level(PrivilegeLevel level) {
			//This is bits 5 and 6 of the byte at offset 40
			entry = set_bits(entry, 40 + 5, 2, (uint64_t) level);
		}
		gdt_entry::PrivilegeLevel gdt_entry::get_privilege_level() {
			return (PrivilegeLevel) get_bits(entry, 40 + 5, 2);
		}
		
		void gdt_entry::set_is_executable(bool isExecutable) {
			//Bit 3 offset 40
			//Make sure isExecutable is only one bit wide
			entry = set_bits(entry, 40 + 3, 1, (uint64_t)(!!isExecutable));
		}
		bool gdt_entry::get_is_executable() {
			return get_bits(entry, 40 + 3, 1);
		}
		
		void gdt_entry::set_data_segment_direction(DataSegmentDirection direction) {
			//Bit 2 offset 40
			entry = set_bits(entry, 40 + 2, 1, (uint64_t) direction);
		}
		gdt_entry::DataSegmentDirection gdt_entry::get_data_segment_direction() {
			return (DataSegmentDirection) get_bits(entry, 40 + 2, 1);
		}
		
		void gdt_entry::set_code_segment_direction(CodeSegmentConform privilege) {
			//Same bit as the data segment
			set_data_segment_direction((DataSegmentDirection) privilege);
		}
		gdt_entry::CodeSegmentConform gdt_entry::get_code_segment_direction() {
			//Same bit as the data segment
			return (CodeSegmentConform) get_data_segment_direction();
		}
		
		void gdt_entry::set_read_write_access(bool rw) {
			//Bit 1 offset 40
			entry = set_bits(entry, 40 + 1, 1, (uint64_t) rw);
		}

		bool gdt_entry::get_read_write_access() {
			return get_bits(entry, 40 + 1, 1);
		}
		
		bool gdt_entry::get_is_accessed() {
			//Bit 0 offset 40
			return get_bits(entry, 40 + 0, 1);
		}

		void gdt_entry::set_granularity(Granularity gran) {
			//Bit 3 offset 52
			entry = set_bits(entry, 52 + 3, 1, (uint64_t) gran);
		}
		gdt_entry::Granularity gdt_entry::get_granularity() {
			return (Granularity) get_bits(entry, 52 + 3, 1);
		}
		
		uint64_t gdt_entry::get_entry() {
			return entry;
		}

		
		bool gdt::add_entry(gdt_entry& entry) {
			if(size >= 8192) {
				return false;
			}
			table[++size] = entry;
			return true;
		}
		
		gdt::gdt() {
			gdt_entry null_entry;
			table[0] = null_entry;
		}

		gdt_entry& gdt::operator[](size_t index) {
			return table[index];
		}
		
		void gdt::install() {
			//Fill the table
			for(int i = 0; i < size; i++) {
				entry_table[i] = table[i].get_entry();
			}
			//Clear interrupts because they are dangerous
			_cli();
			struct {
				uint16_t size;
				uint64_t* table;
			} global_desc_table = {(uint16_t)((uint32_t)size * 8), entry_table};
			//Create a pointer to the table and load it!
			_lgdt(&global_desc_table);
			//It's up to someone else to create the interrupts
		}

	}
}
