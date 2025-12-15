#include <machine/syscall.h>
#include <sys/types.h>
#include "internal_syscall.h"

/* Read from a file.  */
ssize_t _read(int file, void *ptr, size_t len)
{
  // We only care about reading from stdin.
  if (file != 0)
    return -1;

  static uint64_t total_read = 0;

  uint64_t avail = *((uint64_t *) 0x90000008);
  if (avail <= total_read)
    return -1;

  avail -= total_read;
  len = avail < len ? avail : len;

  memcpy(ptr, ((void *) (0x90000010 + total_read)), len);
  total_read += len;
  return len;
}
