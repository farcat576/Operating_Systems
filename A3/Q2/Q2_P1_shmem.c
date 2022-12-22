#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>

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

char* generate(int size){
	const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
	char* sentence = (char*) malloc(size*sizeof(char));
	for(int j=0;j<size-1;j++){
		sentence[j]=alphabet[rand()%(int) (sizeof(alphabet)-1)];
	}	
	sentence[size-1]='\0';
	return sentence;
}

int main(){
	struct timespec start,end;
	clock_gettime(CLOCK_REALTIME,&start);
	char* sentence[50];
	srand((unsigned) time(NULL));
	for (int i=0;i<50;i++){
		sentence[i]=(char *)malloc(sizeof(char*));
		strcpy(sentence[i],generate(21));
	}
	
	struct stat sb;
	int i=0;
	int shared = shm_open("/shared", O_CREAT|O_RDWR,00666);
		if (shared<0){
			perror("Error creating shared memory shared");
			return EXIT_FAILURE;
		}
		if (ftruncate(shared,SHMEM_SIZE)<0){
			perror("Could not trucnate file");
		}
	for (;i<50;){
		sleep(2);
		struct share_mem* pass = (struct share_mem*) mmap(NULL,SHMEM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0);
		if (pass==MAP_FAILED){
			perror("Unable to map memory");
		}
		memcpy(pass->s0,sentence[5*i],21*sizeof(char));
		pass->p0=i;
		memcpy(pass->s1,sentence[5*i+1],21*sizeof(char));
		pass->p1=i+1;
		memcpy(pass->s2,sentence[5*i+2],21*sizeof(char));
		pass->p2=i+2;
		memcpy(pass->s3,sentence[5*i+3],21*sizeof(char));
		pass->p3=i+3;
		memcpy(pass->s4,sentence[5*i+4],21*sizeof(char));
		pass->p4=i+4;
		pass->id=-1;
		munmap(pass,SHMEM_SIZE);
		
		while(1){
			sleep(1);
			struct share_mem* pass = (struct share_mem*) mmap(NULL,SHMEM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0);
			if (pass==MAP_FAILED){
				perror("Unable to map memory");
				continue;
			}
			if (pass->id<0){
				continue;
			}
			
			if (pass->id==i+4){
				printf("Success\n");
				i+=5;
			}
			else{
				printf("Failure: %d\n",pass->id);
			}
			break;
		}
	}
	clock_gettime(CLOCK_REALTIME,&end);
	long sec = end.tv_sec-start.tv_sec;
	long nsec = end.tv_nsec-start.tv_nsec;
	double final = sec + nsec*1e-9;
	printf("Time measured: %.9f seconds.\n",final);
	exit(EXIT_SUCCESS);
}
