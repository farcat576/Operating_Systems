#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int forks[5]={0,0,0,0,0};
pthread_mutex_t lock;

void* CS(void *argv){
	int f1=-1;
	int f2=-1;
	int num= *((int *)argv);
	
	printf("Philosopher %d thinks\n",num);
	sleep(1);
	
	while (f1==-1||f2==-1){
		if(forks[num-1]==0){
			if(f1==-1){
				forks[num-1]=1;
				f1=num;
			}
		}
		if(forks[num%5]==0){
			if(f2==-1){
				forks[num%5]=1;
				f2=num%5+1;
			}
		}
	}
	printf("Philosopher %d picks up fork %d\n",num,f1);
	printf("Philosopher %d picks up fork %d\n",num,f2);
	
	printf("Philosopher %d eats with forks %d and %d\n",num,f1,f2);
	sleep(5);
	
	if(f1>0){
		forks[num-1]=0;
	}
	printf("Philosopher %d puts down fork %d\n",num,f1);
	f1=-1;
	
	if(f2>0){
		forks[num%5]=0;
	}
	printf("Philosopher %d puts down fork %d\n",num,f2);
	f2=-1;
}

int main(){
	pthread_t thread[5];
	int num[5]={1,2,3,4,5};
	while(1){
		if (pthread_create(&thread[0],NULL,CS,(void *) &num[0]) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_create(&thread[2],NULL,CS,(void *) &num[2]) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_join(thread[0],NULL) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_join(thread[2],NULL) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_create(&thread[4],NULL,CS,(void *) &num[4]) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_create(&thread[1],NULL,CS,(void *) &num[1]) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_join(thread[4],NULL) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_join(thread[1],NULL) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_create(&thread[3],NULL,CS,(void *) &num[3]) != 0){
			perror("Failed to create a thread");
			return 1;
		}
		if (pthread_join(thread[3],NULL) != 0){
			perror("Failed to create a thread");
			return 1;
		}
	}
}
