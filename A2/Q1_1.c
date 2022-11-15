#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void *countA(void* arg){
	for(int i=1;i>0;i++);
}

void *countB(void* arg){
	for(int i=1;i>0;i++);
}

void *countC(void* arg){
	for(int i=1;i>0;i++);
}

int main(){
	pthread_t Thr[3];
	struct sched_param param;
	struct timespec start,end;
	pthread_attr_t attr;
	clock_gettime(CLOCK_REALTIME,&start);
	
	if (pthread_create(&Thr[0],NULL,countA,NULL)){
		perror("Failed to create a thread");
		return 1;
	}
	else{
		pthread_attr_getschedparam(&attr,&param);
		param.sched_priority=0;
		printf("%d\n",pthread_setschedparam(Thr[0],SCHED_OTHER,&param));
		printf("Thr says Hi!\n");
	}
	
	if (pthread_create(&Thr[1],NULL,countB,NULL) != 0){
		perror("Failed to create a thread");
		return 1;
	}
	else{
		pthread_attr_getschedparam(&attr,&param);
		param.sched_priority=1;
		printf("%d\n",pthread_setschedparam(Thr[1],SCHED_RR,&param));
		printf("Thr says Hi!\n");
	}
	
	if (pthread_create(&Thr[2],	NULL,countC,NULL) != 0){
		perror("Failed to create a thread");
		return 1;
	}
	else{
		pthread_attr_getschedparam(&attr,&param);
		param.sched_priority=1;
		printf("%d\n",pthread_setschedparam(Thr[2],SCHED_FIFO,&param));
		printf("Thr says Hi!\n");
	}
	
	for(int i=0;i<3;i++){
		if (pthread_join(Thr[i],NULL) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		else{
			clock_gettime(CLOCK_REALTIME,&end);
			long sec = end.tv_sec-start.tv_sec;
			long nsec = end.tv_nsec-start.tv_nsec;
			double final = sec + nsec*1e-9;
			printf("Time measured: %.9f seconds.\n",final);
		}
	}
}
