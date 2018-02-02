OUTPUT_FORMAT(elf64-littleaarch64)

SECTIONS
{
  .text : ALIGN(0x1000) {
NORELOC_TEXT_START_ = .;
    KEEP(crt0.nso.o(.text*))
    KEEP(crt0.nro.o(.text*))
    *(.text .text*)
    *(.plt .plt*)
NORELOC_TEXT_END_ = .;
  }

  .rodata : ALIGN(0x1000) {
NORELOC_RODATA_START_ = .;
    *(.rodata .rodata*)
    *(.gcc_except_table)
NORELOC_RODATA_END_ = .;
  }

  .rela.dyn : ALIGN(8) {
NORELOC_RELA_START_ = .;
    *(.rela.dyn)
  }

  .data : ALIGN(0x1000) {
NORELOC_DATA_START_ = .;
    KEEP(crt0.nso.o(.data))
    KEEP(crt0.nro.o(.data))
    *(.data .data*)
NORELOC_GOT_START_ = .;
    *(.got .got*)
NORELOC_GOT_PLT_START_ = .;
    *(.got.plt .got.plt*)
NORELOC_DATA_END_ = .;
  }

  .dynamic : ALIGN(0x8) {
NORELOC_DYNAMIC_START_ = .;
    *(.dynamic)
NORELOC_DYNAMIC_END_ = .;
  }

  .dynsym : ALIGN(0x1000) {
NORELOC_DYNSYM_START_ = .;
    *(.dynsym .dynsym*)
NORELOC_DYNSYM_END_ = .;
  }

  .dynstr : ALIGN(0x8) {
NORELOC_DYNSTR_START_ = .;
    *(.dynstr .dynstr*)
NORELOC_DYNSTR_END_ = .;
  }

  .bss : ALIGN(0x1000) {
NORELOC_BSS_START_ = .;
    *(.bss)
    *(COMMON)
NORELOC_BSS_END_ = .;
  }

  .hash : {
    *(.hash)
  }

  .eh_frame : ALIGN(0x1000) {
    __eh_frame_start = .;
    *(.eh_frame)
    __eh_frame_end = .;
  }

  .eh_frame_hdr : ALIGN(0x1000) {
    __eh_frame_hdr_start = .;
    *(.eh_frame_hdr)
    __eh_frame_hdr_end = .;
  }

  /DISCARD/ : {
    *(.comment)
    *(.note.GNU-stack)
  }
}
