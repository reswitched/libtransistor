OUTPUT_FORMAT(elf64-littleaarch64)
OUTPUT_ARCH(aarch64)
ENTRY(_start)

PHDRS
{
  text PT_LOAD FLAGS(5);
  rodata PT_LOAD FLAGS(4);
  data PT_LOAD FLAGS(6);
  bss PT_LOAD FLAGS(6);
}

SECTIONS
{
  . = 0;

  .text : ALIGN(0x1000) {
    __text_start = .;
    KEEP(crt0.nso.o(.text.jmp))
    KEEP(crt0.nro.o(.text.jmp))

    . = 0x4;
    LONG(_mod_header - __text_start);

    . = 0x80;

    *(.text .text*)
    *(.plt .plt*)
  }

  /* Read-only sections */

  . = ALIGN(0x1000);

  .rodata : { *(.rodata .rodata*) } :rodata
  .mod0 : {
    KEEP(crt0.nso.o(.data.mod0))
    KEEP(crt0.nro.o(.data.mod0))
  }
  .hash : { *(.hash) }
  .dynsym : { *(.dynsym .dynsym*) }
  .dynstr : { *(.dynstr .dynstr*) }
  .rela.dyn : { *(.rela.dyn) }

  .eh_frame : {
    __eh_frame_start = .;
    *(.eh_frame .eh_frame*)
    __eh_frame_end = .;
  }

  .eh_frame_hdr : {
    __eh_frame_hdr_start = .;
    *(.eh_frame_hdr .eh_frame_hdr*)
    __eh_frame_hdr_end = .;
  }

  /* Read-write sections */

   . = ALIGN(0x1000);

  .data : {
    *(.data .data*)
    *(.got .got*)
    *(.got.plt .got.plt*)
  } :data

  .dynamic : {
    __dynamic_start = .;
    *(.dynamic)
  }

  /* BSS section */

  . = ALIGN(0x1000);

  .bss : {
    __bss_start = .;
    *(.bss .bss*)
    *(COMMON)
    __bss_end = .;
  } :bss
}
