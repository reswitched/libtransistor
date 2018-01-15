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
	.word NORELOC__nro_modhdr - NORELOC__filestart

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
        .word 0
.section .text, "e"
start:
        adrp x1, _start // aslr base
	bl _libtransistor_start
loop:
	b loop

.global _get_module_header
_get_module_header:
        adrp x0, _mod_header
        add x0, x0, #:lo12:_mod_header
        ret
