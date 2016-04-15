/* multiboot.h - Multiboot header file. */
/* Copyright (C) 1999,2003,2007,2008,2009  Free Software Foundation, Inc.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to
*  deal in the Software without restriction, including without limitation the
*  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
*  sell copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL ANY
*  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
*  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef MULTIBOOT_HEADER2
.set MULTIBOOT_HEADER2, 1

/* How many bytes from the start of the file we search for the header. */
.set MULTIBOOT_SEARCH,                        8192

/* The magic field should contain this. */
.set MULTIBOOT_HEADER_MAGIC,                  0x1BADB002

/* This should be in %eax. */
.set MULTIBOOT_BOOTLOADER_MAGIC,              0x2BADB002

/* The bits in the required part of flags field we don't support. */
.set MULTIBOOT_UNSUPPORTED,                   0x0000fffc

/* Alignment of multiboot modules. */
.set MULTIBOOT_MOD_ALIGN,                     0x00001000

/* Alignment of the multiboot info structure. */
.set MULTIBOOT_INFO_ALIGN,                    0x00000004

/* Flags set in the 'flags' member of the multiboot header. */

/* Align all boot modules on i386 page (4KB) boundaries. */
.set MULTIBOOT_PAGE_ALIGN,                    0x00000001

/* Must pass memory information to OS. */
.set MULTIBOOT_MEMORY_INFO,                   0x00000002

/* Must pass video information to OS. */
.set MULTIBOOT_VIDEO_MODE,                    0x00000004

/* This flag indicates the use of the address fields in the header. */
.set MULTIBOOT_AOUT_KLUDGE,                   0x00010000

/* Flags to be set in the 'flags' member of the multiboot info structure. */

/* is there basic lower/upper memory information? */
.set MULTIBOOT_INFO_MEMORY,                   0x00000001
/* is there a boot device set? */
.set MULTIBOOT_INFO_BOOTDEV,                  0x00000002
/* is the command-line defined? */
.set MULTIBOOT_INFO_CMDLINE,                  0x00000004
/* are there modules to do something with? */
.set MULTIBOOT_INFO_MODS,                     0x00000008

/* These next two are mutually exclusive */

/* is there a symbol table loaded? */
.set MULTIBOOT_INFO_AOUT_SYMS,                0x00000010
/* is there an ELF section header table? */
.set MULTIBOOT_INFO_ELF_SHDR,                 0X00000020

/* is there a full memory map? */
.set MULTIBOOT_INFO_MEM_MAP,                  0x00000040

/* Is there drive info? */
.set MULTIBOOT_INFO_DRIVE_INFO,               0x00000080

/* Is there a config table? */
.set MULTIBOOT_INFO_CONFIG_TABLE,             0x00000100

/* Is there a boot loader name? */
.set MULTIBOOT_INFO_BOOT_LOADER_NAME,         0x00000200

/* Is there a APM table? */
.set MULTIBOOT_INFO_APM_TABLE,                0x00000400

/* Is there video information? */
.set MULTIBOOT_INFO_VIDEO_INFO,               0x00000800

#endif //MULTIBOOT_HEADER2
