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
        b start
	.fill 0x7c, 1, 0

.section .data, "e"
	.word 0, 8
NORELOC__nro_modhdr:
.global _mod_header
_mod_header:
        .ascii "MOD0"
	.word NORELOC_DYNAMIC_START_ - NORELOC__nro_modhdr
	.word NORELOC_BSS_START_ - NORELOC__nro_modhdr
	.word NORELOC_BSS_END_ - NORELOC__nro_modhdr
	.word 0, 0 // eh_frame_hdr start/end
	.word 0 // runtime-generated module object offset
.global IS_NRO
IS_NRO: 
        .word 1
        
.section .text, "e"
.global start
start:
        adrp x2, _start // aslr base

        // set LR to svcExitProcess if it's null
        adrp x3, svcExitProcess
        cmp x30, xzr
        csel x30, x3, x30, eq

        sub sp, sp, 0x10
        stp x29, x30, [sp]
        bl _libtransistor_start
        ldp x29, x30, [sp], 0x10
        ret
