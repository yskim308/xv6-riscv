#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(void)
{
  settickets(100);
  int child_pids[3];

  for (int i = 1; i <= 3; ++i) {
    int rc = fork();
    if (rc == 0) {
      settickets(i * 10);
      for (;;) {
      }
    } else if (rc > 0) {
      child_pids[i - 1] = rc;
    }
  }

  printf("timestep, pid, tickets, ticks\n");

  for (int i = 0; i < 30; ++i) {
    pause(5);

    struct pstat p;
    getpinfo(&p);

    for (int j = 0; j < NPROC; ++j) {
      if (p.inuse[j] == 0)
        continue;

      if (p.pid[j] == child_pids[0] || p.pid[j] == child_pids[1] ||
          p.pid[j] == child_pids[2]) {
        printf("%d, %d, %d, %d\n", i, p.pid[j], p.tickets[j], p.ticks[j]);
      }
    }
  }

  for (int i = 0; i < 3; ++i) {
    kill(child_pids[i]);
    wait(0);
  }

  exit(0);
}
