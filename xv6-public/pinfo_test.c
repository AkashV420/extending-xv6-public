#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "pinfo.h"

int main(int argc, char *argv[])
{
    struct proc_stat p;

    pinfo(&p);
    printf(1, "process %s with id %d\nruntime : %d ticks\nnum_run : %d\ncurr_q : %d\nticks : %d %d %d %d %d\n", argv[1], p.pid, p.rtime, p.num_run, p.curr_q, p.ticks[0], p.ticks[1], p.ticks[2], p.ticks[3], p.ticks[4]);

    for (int i = 0; i < 500; i++)
        printf(1, "%d", i);
    printf(1, "\n");
    pinfo(&p);
    printf(1, "process %s with id %d\nruntime : %d ticks\nnum_run : %d\ncurr_q : %d\nticks : %d %d %d %d %d\n", argv[1], p.pid, p.rtime, p.num_run, p.curr_q, p.ticks[0], p.ticks[1], p.ticks[2], p.ticks[3], p.ticks[4]);

    for (int i = 0; i < 500; i++)
        printf(1, "%d", i);
    printf(1, "\n");
    pinfo(&p);
    printf(1, "process %s with id %d\nruntime : %d ticks\nnum_run : %d\ncurr_q : %d\nticks : %d %d %d %d %d\n", argv[1], p.pid, p.rtime, p.num_run, p.curr_q, p.ticks[0], p.ticks[1], p.ticks[2], p.ticks[3], p.ticks[4]);

    exit();
    return 0;
}