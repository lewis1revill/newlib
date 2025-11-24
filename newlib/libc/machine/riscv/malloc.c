#include <stdlib.h>

volatile void *heap_pos = 0;

/* The user-visible malloc (renamed by compiler).  */
void *malloc (size_t size)
{
  // TODO: alignment, etc.
  void *heap_bottom;
  asm volatile ("la %0, _kernel_heap_bottom" : "=r"(heap_bottom));

  if (((size_t) heap_pos) == 0)
    heap_pos = heap_bottom;

  void *ptr = heap_pos;
  heap_pos += size;
  return ptr;
}
