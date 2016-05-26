.section .init
        #; gcc puts crtend here
        popq %rbp
        ret

.section .fini
        #; gcc puts crtend here
        popq %rbp
        ret
