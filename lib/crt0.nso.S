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
	.ascii "MOD0"
	.word NORELOC_DYNAMIC_START_ - NORELOC__nro_modhdr
	.word NORELOC_BSS_START_ - NORELOC__nro_modhdr
	.word NORELOC_BSS_END_ - NORELOC__nro_modhdr
	.word 0, 0 // eh_frame_hdr start/end
	.word 0 // runtime-generated module object offset

.section .text, "e"
start:
	bl main
loop:
.global _exit
_exit:  
	b loop
