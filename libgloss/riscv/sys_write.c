#include <machine/syscall.h>
#include <sys/types.h>
#include "internal_syscall.h"

/* Write to a file.  */
ssize_t
_write(int file, const void *ptr, size_t len)
{
  // We only care about writing to stdout (also we allow stderr to redirect to
  // the same output location).
  if (file != 1 && file != 2)
    return -1;

  volatile char *out = (void *) 0x10000000;
  size_t arch_id;

  asm volatile ("csrr %0, marchid" : "=r"(arch_id));

  if (arch_id == 0xFFFEEEE)
    out = (char *) 0xa0000200;

  for (size_t i = 0; i < len; ++i)
    *out = ((char *)ptr)[i];

  return len;

  // return syscall_errno (SYS_write, 3, file, ptr, len, 0, 0, 0);
}
