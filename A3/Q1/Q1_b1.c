#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int forks[5]={0,0,0,0,0};
int philo[5]={0,0,0,0,0};
int sauce[2]={0,0};
int sauce_pointer=0;

void* CS(void *argv){
	int f1=-1;
	int f2=-1;
	int s0=-1;
	int num= *((int *)argv);
	
	printf("Philosopher %d thinks\n",num);
	sleep(1);
	
	philo[num-1]=-1;
	while(1){
		if(philo[num%5]!=1&&philo[(num-2)%5]!=1){
			if(forks[num-1]==0){
				forks[num-1]=1;
				f1=num;
				break;
			}
		}
	}
	printf("Philosopher %d picks up fork %d\n",num,f1);
	while(1){
		if(philo[num%5]!=1&&philo[(num-2)%5]!=1){
			if(forks[num%5]==0){
				forks[num%5]=1;
				f2=num%5+1;
				break;
			}
		}
	}
	while(1){
		if(sauce[sauce_pointer]==0){
			sauce[sauce_pointer]==1;
			s0=sauce_pointer+1;
			sauce_pointer=1-sauce_pointer;
			break;
		}
	}
	printf("Philosopher %d picks up fork %d\n",num,f2);
	
	philo[num-1]=1;
	printf("Philosopher %d eats with forks %d and %d, along with sauce bowl %d\n",num,f1,f2,s0);
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
	
	if(s0>0){
		sauce[s0-1]=0;
	}
	printf("Philosopher %d puts down sauce bowl %d\n",num,s0);
	philo[num-1]=0;
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
