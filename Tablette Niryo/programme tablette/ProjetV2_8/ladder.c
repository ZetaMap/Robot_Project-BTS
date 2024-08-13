#include "hmiworks.h"

extern int ladder_projetv2_8_ldx(int);


BYTE ladder_main(BYTE en)
{
  ladder_projetv2_8_ldx(en);
  return 1;
}

