#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int forks[5]={0,0,0,0,0};
int philo[5]={0,0,0,0,0};
int sauce[2]={0,0};
int sauce_pointer=0;
sem_t sem1,sem2,sem3;

void* CS(void *argv){
	int f1=-1;
	int f2=-1;
	int s0=-1;
	int num= *((int *)argv);
	
	while(1){
	printf("Philosopher %d thinks\n",num);
	sleep(1);
	
	philo[num-1]=-1;
	sem_wait(&sem1);
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
	sem_wait(&sem2);
	while(1){
		if(philo[num%5]!=1&&philo[(num-2)%5]!=1){
			if(forks[num%5]==0){
				forks[num%5]=1;
				f2=num%5+1;
				break;
			}
		}
	}
	sem_wait(&sem3);
	while(1){
		if(sauce[sauce_pointer]==0){
			sauce[sauce_pointer]==1;
			s0=sauce_pointer+1;
			sauce_pointer=1-sauce_pointer;
			break;
		}
	}
	sem_post(&sem3);
	sem_post(&sem2);
	sem_post(&sem1);
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
}

int main(){
	pthread_t thread[5];
	int num[5]={1,2,3,4,5};
	sem_init(&sem1,0,1);
	sem_init(&sem2,0,1);
	sem_init(&sem3,0,1);
	for (int i=0;i<5;i++){
		if (pthread_create(&thread[i],NULL,CS,(void *) &num[i]) != 0){
			perror("Failed to create a thread");
			return 1;
		}
	}
	for (int i=0;i<5;i++){
		if (pthread_join(thread[i],NULL) != 0){
			perror("Failed to create a thread");
			return 1;
		}
	}
}
