.section .init
.global _init
.type _init, @function
_init:
        push %ebp
        movl %esp, %ebp
        #; gcc puts crtbegin.o here
		#;call _init_proc

.section .fini
.global _fini
.type _fini, @function
_fini:
        push %ebp
        movl %esp, %ebp
        #; gcc puts crtbegin here
		#;call _term_proc
