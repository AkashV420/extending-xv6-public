#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(void)
{
    // struct proc_stat p;

    int pid;
    for (int i = 0; i < 10; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            sleep((10-i)*100);
            while (1)
                printf(1, "%d ", i);
        }
        sleep(10);
    }
    while(1);
}