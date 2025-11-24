#include <machine/syscall.h>
#include <sys/types.h>
#include "internal_syscall.h"

/* Read from a file.  */
ssize_t _read(int file, void *ptr, size_t len)
{
  // We only care about reading from stdin.
  if (file != 0)
    return -1;

  return syscall_errno (SYS_read, 3, file, ptr, len, 0, 0, 0);
}
