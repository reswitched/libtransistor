.hidden NORELOC__filestart
.global NORELOC__nro_modhdr
.hidden NORELOC__nro_modhdr

.hidden NORELOC_TEXT_START_
.hidden NORELOC_TEXT_END_
.hidden NORELOC_RODATA_START_
.hidden NORELOC_DYNSTR_START_
.hidden NORELOC_DYNSYM_START_
.hidden NORELOC_RODATA_END_
.hidden NORELOC_DATA_START_
.hidden NORELOC_DYNAMIC_START_
.hidden NORELOC_GOT_START_
.hidden NORELOC_GOT_PLT_START_
.hidden NORELOC_DATA_END_
.hidden NORELOC_BSS_START_
.hidden NORELOC_BSS_END_

.section .text, "e"
NORELOC__filestart:
.global _start
_start:
	.fill 0x80, 1, 0

.section .data, "e"
	.word 0, 8
NORELOC__nro_modhdr:
        .ascii "MOD0"
	.word NORELOC_DYNAMIC_START_ - NORELOC__nro_modhdr
	.word NORELOC_BSS_START_ - NORELOC__nro_modhdr
	.word NORELOC_BSS_END_ - NORELOC__nro_modhdr
	.word 0, 0 // eh_frame_hdr start/end
	.word 0 // runtime-generated module object offset
        .quad log_buffer
        .quad log_length
        
.section .text, "e"
.global start
start:
        sub sp, sp, 0x10
        stp x29, x30, [sp]
        //ldr x1, __crt0_exit_frame
        //stp x29, x30, [x1]
        bl main
        ldp x29, x30, [sp], 0x10
        ret

.global _exit
_exit:
        //ldr x1, __crt0_exit_frame
        //ldp x29, x30, [x1]
        //ret
        b _exit
        
.section .bss
__crt0_exit_frame:       
        .quad 0
        .quad 0
