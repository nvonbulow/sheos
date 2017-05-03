#ifndef __KERNEL_GDT_H__
#define __KERNEL_GDT_H__

#include <stdint.h>
#include <stddef.h>

namespace kernel {
    namespace memory {
        
        //Prefer paging over segmentation because the processor handles it automatically
        
        class gdt_entry {
        private:
            uint8_t get_access_byte();
            uint8_t get_flags();
            void set_access_byte(uint8_t b);
            void set_flags(uint8_t flags);
        public:
            gdt_entry(gdt_entry& value);
            /*
             * Default value:
             * Privilege = highest
             * Executable = false
             * Direction/Conformation = grows up / only this ring can execute
             * Read/Write = false
             * Accessed = false
             * Granularity = 1 byte blocks
             * Mode: 32 bit protected mode only
             * 
             * Base Address: 0x00000000
             * Limit Address: 0x00000
             */
            gdt_entry();
            
            void set_base_address(void* address);
            void* get_base_address();
            
            //Only allows 20 bit values!!
            void set_limit_address(void* address);
            void* get_limit_address();
            
            enum class PrivilegeLevel {
                Ring0 = 0,
                Ring1 = 1,
                Ring2 = 2,
                Ring3 = 3
            };
            
            void set_privilege_level(PrivilegeLevel level);
            PrivilegeLevel get_privilege_level();
            
            void set_is_executable(bool isExecutable);
            bool get_is_executable();
            
            enum class DataSegmentDirection {
                DirectionSegmentUp = 0,
                DirectionSegmentDown = 1,
            };
            enum class CodeSegmentConform {
                EqualLowerPrivilege = 1,
                EqualPrivilege = 0
            };
            
            void set_data_segment_direction(DataSegmentDirection direction);
            DataSegmentDirection get_data_segment_direction();
            
            void set_code_segment_direction(CodeSegmentConform privilege);
            CodeSegmentConform get_code_segment_direction();
            
            void set_read_write_access(bool access);
            bool get_read_write_access();
            
            bool get_is_accessed();
            
            enum class Granularity {
                ByteGranularity = 0,
                PageGranularity = 1
            };
            
            void set_granularity(Granularity gran);
            Granularity get_granularity();
            
            uint64_t get_entry();
		private:
                    uint64_t entry;
        };
        
        class gdt {
        private:
            gdt_entry table[8192];
            uint16_t size = 0;
        public:
            gdt();
            bool add_entry(gdt_entry& entry);
            gdt_entry& operator[](size_t index);
            void install();
        };
        
    }
}

#endif //__KERNEL_GDT_H__

