#include "kernel/types.h"
#include "user.h"

int
main()
{
  int *p = 0;
  int c = *p;
  printf("%d", c);
  return 0;
}
