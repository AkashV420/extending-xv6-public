#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char *argv[])
{
	int cpid;
	int status, rtime, wtime;
	printf(1, "Running time\n");
	cpid = fork();
	if(cpid == 0) {
		exec(argv[1], &argv[1]);
		printf(1, "exec %s failed\n", argv[1]);
		exit();
	} else {
		status = waitx(&wtime, &rtime);
		printf(1,"wait time = %d\nrun time = %d\nreturn value = %d\n", wtime, rtime, status);
		exit();
	}
	return 0;
}