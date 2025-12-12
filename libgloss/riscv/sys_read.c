#include <machine/syscall.h>
#include <sys/types.h>
#include "internal_syscall.h"

/* Read from a file.  */
ssize_t _read(int file, void *ptr, size_t len)
{
  // We only care about reading from stdin.
  if (file != 0)
    return -1;

  uint64_t avail = 0; 
  while (!avail)
    avail = *((uint64_t *) 0x90000008);

  memcpy(ptr, ((void *) 0x90000010), avail);
  return avail;
}
