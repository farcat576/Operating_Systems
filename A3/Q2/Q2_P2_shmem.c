#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

#define max(a,b) (a<b) ? b : a;
#define SHMEM_SIZE 5*(21*sizeof(char)+sizeof(int))+sizeof(int)
#define Q2_SEM1 "/Q2_sem1"
#define Q2_SEM2 "/Q2_sem2"

struct share_mem{
	char s0[21];
	char s1[21];
	char s2[21];
	char s3[21];
	char s4[21];
	int p0;
	int p1;
	int p2;
	int p3;
	int p4;
	int id;
};

int main(){

	int shared = shm_open("/shared", O_CREAT|O_RDWR,00666);
		if (shared<0){
			perror("Error opening shared memory shared");
			return EXIT_FAILURE;
		}

	int i=0;
	int max=-1;
	for(;i<50;){
		int max=-1;
		sleep(3);
		struct share_mem *data=(struct share_mem*)malloc(sizeof(struct share_mem));
		while(1){
			sleep(2);
			data = (struct share_mem*) mmap(NULL,SHMEM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0);
			if (data==MAP_FAILED){
				perror("Unable to map memory");
				exit(EXIT_SUCCESS);
			}
			if(data->id<0) break;
		}
	
		printf("%d\n",data->p0);
		max=max(max,data->p0);
		printf("%d\n",data->p1);
		max=max(max,data->p1);
		printf("%d\n",data->p2);
		max=max(max,data->p2);
		printf("%d\n",data->p3);
		max=max(max,data->p3);
		printf("%d\n",data->p4);
		max=max(max,data->p4);
		printf("%s\n",data->s0);
		printf("%s\n",data->s1);
		printf("%s\n",data->s2);
		printf("%s\n",data->s3);
		printf("%s\n",data->s4);

		if(max==i+4){
			i=max+1;
			data->id=max;
			munmap(data,SHMEM_SIZE);
		}

	}
	exit(EXIT_SUCCESS);
}
