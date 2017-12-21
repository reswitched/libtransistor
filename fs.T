OUTPUT_FORMAT(elf64-littleaarch64)

SECTIONS
{
  .data : {
    _libtransistor_squashfs_image = .;
    *(.data .data*)
    _libtransistor_squashfs_image_end = .;
  }
}