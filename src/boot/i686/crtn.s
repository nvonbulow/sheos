.section .init
        #; gcc puts crtend here
        popl %ebp
        ret

.section .fini
        #; gcc puts crtend here
        popl %ebp
        ret
