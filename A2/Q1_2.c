#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t pid[3];
	struct sched_param param;
	struct timespec start,end;
	int status=0;
	
	clock_gettime(CLOCK_REALTIME,&start);
	pid[0]=fork();
	if(pid[0]>0){
		waitpid(-1,&status,WUNTRACED|WCONTINUED);
	}
	else if (pid[0]==0){
		sched_getparam(pid[0],&param);
		param.sched_priority=0;
		printf("%d\n",sched_setscheduler(pid[0],SCHED_OTHER,&param));
		//if (execve(argv[0],argv,NULL)==-1){
		//	perror("Could not use execvp");
		//}
		clock_gettime(CLOCK_REALTIME,&end);
		long sec = end.tv_sec-start.tv_sec;
		long nsec = end.tv_nsec-start.tv_nsec;
		double final = sec + nsec*1e-9;
		printf("Time measured: %.9f seconds.\n",final);
		abort();
	}
	else{
		perror("Error while forking");
	}
	
	clock_gettime(CLOCK_REALTIME,&start);
	pid[1]=fork();
	if(pid[1]>0){
		waitpid(-1,&status,WUNTRACED|WCONTINUED);
	}
	else if (pid[1]==0){
		sched_getparam(pid[1],&param);
		param.sched_priority=1;
		printf("%d\n",sched_setscheduler(pid[1],SCHED_RR,&param));
		//if (execve(argv[0],argv,NULL)==-1){
		//	perror("Could not use execvp");
		//}
		clock_gettime(CLOCK_REALTIME,&end);
		long sec = end.tv_sec-start.tv_sec;
		long nsec = end.tv_nsec-start.tv_nsec;
		double final = sec + nsec*1e-9;
		printf("Time measured: %.9f seconds.\n",final);
		abort();
	}
	else{
		perror("Error while forking");
	}
	
	clock_gettime(CLOCK_REALTIME,&start);
	pid[2]=fork();
	if(pid[2]>0){
		waitpid(-1,&status,WUNTRACED|WCONTINUED);
	}
	else if (pid[2]==0){
		sched_getparam(pid[2],&param);
		param.sched_priority=1;
		printf("%d\n",sched_setscheduler(pid[2],SCHED_FIFO,&param));
		//if (execve(argv[0],argv,NULL)==-1){
		//	perror("Could not use execvp");
		//}
		clock_gettime(CLOCK_REALTIME,&end);
		long sec = end.tv_sec-start.tv_sec;
		long nsec = end.tv_nsec-start.tv_nsec;
		double final = sec + nsec*1e-9;
		printf("Time measured: %.9f seconds.\n",final);
		abort();
	}
	else{
		perror("Error while forking");
	}
}
