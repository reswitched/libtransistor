#include<libtransistor/nx.h>

int main() {
  svcSleepThread(100000000);
  
  result_t r;
  if((r = sm_init()) != RESULT_OK) {
    dbg_printf("failed to init sm: 0x%x", r);
    return 1;
  }

  if((r = nv_init()) != RESULT_OK) {
    dbg_printf("failed to init nv: 0x%x, %d", r, nv_errno);
    goto err_only_sm;
  }

  int fd = nv_open("/dev/nvhost-ctrl-gpu");
  if(fd < 0) {
    dbg_printf("failed to open /dev/nvhost-ctrl-gpu");
    goto err_nv;
  }

  dbg_printf("opened /dev/nvhost-ctrl-gpu: 0x%x", fd);
  
  struct {
    uint64_t bufsz;
    uint64_t bufaddr;
    uint8_t characteristics[0xa0];  
  } ioctl_args;
  ioctl_args.bufsz = 0xa0;
  ioctl_args.bufaddr = 1;
  int e;
  if((e = nv_ioctl(fd, 0xC0B04705, &ioctl_args, sizeof(ioctl_args))) != 0) {
    dbg_printf("failed to GET_CHARACTERISTICS: %d, 0x%x, %d", e, nv_result, nv_errno);
    goto err_nvhost_ctrl_gpu;
  }

  hexdump(&ioctl_args, sizeof(ioctl_args));
  
 err_nvhost_ctrl_gpu:
  if(nv_close(fd) != 0) {
    dbg_printf("failed to close /dev/nvhost-ctrl-gpu");
    goto err_nv;
  }
 err_nv:
  nv_finalize();
 err_only_sm:
  sm_finalize();

  return 0;
}
