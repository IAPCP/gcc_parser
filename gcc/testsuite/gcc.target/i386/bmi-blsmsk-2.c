/* { dg-do run { target bmi } } */
/* { dg-options "-O2 -mbmi -fno-inline" } */

#include <x86intrin.h>

#include "bmi-check.h"

/*  Trick compiler in order not to generate target insn here. */
int calc_blsmsk_u32 (int src1, int src2)
{
  return (src1-1) ^ (src2);
}

static void
bmi_test ()
{
  unsigned i;
  int src = 0xfacec0ff;
  int res, res_ref;

  for (i=0; i<5; ++i) {
    src = i + src << i;

    res_ref = calc_blsmsk_u32 (src, src);
    res = __blsmsk_u32 (src);

    if (res != res_ref)
      abort();
  }
}
