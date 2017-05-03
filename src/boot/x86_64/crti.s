.section .init
.global _init
.type _init, @function
_init:
        push %rbp
        movq %rsp, %rbp
        #; gcc puts crtbegin.o here
		#;call frame_dummy

.section .fini
.global _fini
.type _fini, @function
_fini:
        movq %rsp, %rbp
		#;call __do_global_dtors_aux
        #; gcc puts crtbegin here
