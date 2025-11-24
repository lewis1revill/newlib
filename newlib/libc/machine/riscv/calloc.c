#include <stdlib.h>
#include <string.h>

void *
calloc (size_t size, size_t len)
{
  void *p = malloc (size * len);
  if (!p)
    return p;
  return memset (p, 0, size * len);
}
