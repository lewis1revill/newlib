/* Copyright (c) 2017  SiFive Inc. All rights reserved.

   This copyrighted material is made available to anyone wishing to use,
   modify, copy, or redistribute it subject to the terms and conditions
   of the FreeBSD License.   This program is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY expressed or implied,
   including the implied warranties of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  A copy of this license is available at
   http://www.opensource.org/licenses.
*/

#include "newlib.h"

#=========================================================================
# crt0.S : Entry point for RISC-V user programs
#=========================================================================

  .section ".text.init"
  .global _start
  .type   _start, @function
_start:

          # before we use the `la` pseudo-instruction for the first time,
          #  we need to set `gp` (google linker relaxation)
          .option push
          .option norelax
          la gp, _global_pointer
          .option pop

          # set the stack pointer
          la sp, _init_stack_top

          # tail-call to {entry}
          call main
          csrr t0, marchid
          # li   t1, {_ARCH_ID_ZISK}
          li   t1, 0xFFFEEEE
          beq t0, t1, 1f

          # QEmuu exit
          # li t0, {_QEMU_EXIT_ADDR}
          # li t1, {_QEMU_EXIT_CODE}
          li t0, 0x100000
          li t1, 0x5555
          sw t1, 0(t0)
          j 2f

          # Zisk exit
          1: li   a7, 93
          ecall

          2: j 2b
