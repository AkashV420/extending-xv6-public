#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "pstat.h"

int
main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0) {
        set_priority(10, 0);
        double z, d = 1, x = 0;
        int i=0;
        while (i < 5) 
        {
            int j=0;
            while(j < 10) 
            {
                 z = 0;
                while(z < 2000000) 
                {
                    x = x + 3.14 * 89.64; // useless calcs
                    z += d;
                }
                j++;
            }
        i++;
        }
        #ifdef MLFQ
        struct proc_stat ps;
        getpinfo(&ps);
        printf(1, "\nPID == %d\nRun_time = %d\nNum_run = %d\ncurrent_queue=%d\n", ps.pid, ps.runtime, ps.num_run, ps.current_queue);
        printf(1, "ticks : ");
         i=0;
        while(i<5) 
        {
            printf(1, "%d ", ps.ticks[i]);
            i++;
        }
        printf(1,"\n");
        #endif
        printf(1, "test 1 ended\n");
        exit();
    }
    int wtime;
    int rtime;
    waitx(&wtime, &rtime);
    printf(1, "wait = %d run = %d\n", wtime, rtime);
    exit();
}
