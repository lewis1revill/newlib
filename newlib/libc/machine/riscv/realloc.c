#include <stdlib.h>

void *
realloc (void *old_ptr, size_t new_size)
{
  void *new_ptr = malloc (new_size);
  return new_ptr;
}
