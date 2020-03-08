# Implementing Syscalls and Scheduling policies for xv6:

Added FCFS, PBS, MLFQ scheduler and also added new fields ctime, etime and rtime for creation time, end-time and total time respectively of a process.


## For running the program run the command 

    --> make qemu [SCHEDULER = POLICY]  

The POLICY used can be either FCFS, MLFQ or PBS. However, please note that, before switching between policies, do "make clean" once

## Waitx SYSCALL

To implement this function, we added creation time (ctime), Runtime (rtime), and Endtime (etime) to the proc structures. This function just does as mentioned in the PDF, that is assign the total number of clock ticks during which process was waiting and total number of clock ticks when the process was running. This function returns 0 for success and -1 for failure that is, no child process found to kill.

## Implementation of FCFS 

Here, in FCFS (First Come First Serve), we recurse over the ptable and find the running proc with oldest ctime, and execute it first. 


## Implementation of PBC 

Here in PBC (Priority Based Scheduling), we added a new parameter, called priority to the proc structure. Then we recurse over the ptable to find the running proc with highest priority and make it run like in FCFS. In order to set the priority of a process, we use the SYSCALL int setpriority(int priority).


## Implementation of Getpinfo SYSCALL

We need getpinfo SYSCALL to check the details regarding the process passed to it. It returns 0 for success, i.e. process exists and -1 otherwise

## Implementation of MLFQ 

Here in MLFQ (Multi-level Feedback Queue) scheduling, we create multiple(5) queues. In each queue, each process is alloted a particular number of ticks. If the process fails to execute within that time it is demoted to the next queue. Aging implemented, ensures that no process will wait in the lowest priority queue indefinitely.

## Comparison between the different scheduling algorithms

In order to compare the scheduling algorithms, run the benchmark command. We get the following observations:  
    -MLFQ and default implement scheduling in the fastest way
    -MLFQ algorithm, though it is elaborate and difficult to implement, is fast as it handles almost all cases and gives best response time and throughput. 
    -PBS gives a very good response time for real time applications.
    -FCFS is the slowest but it is really easy to implement.

However, in the Implementation of XV6, trap always preempt the running process after each tick. This prevents the MLFQ and all other algorithms from working properly.

<----------------------------------------------------------------------MADE-BY_AKASH-VERMA------------------------------------------------------------------------------>
