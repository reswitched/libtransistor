OUTPUT_FORMAT(elf64-littleaarch64)

SECTIONS
{
  .data : {
    SQUASHFS_IMAGE_START = .;
    *(.data .data*)
    SQUASHFS_IMAGE_END = .;
  }
}