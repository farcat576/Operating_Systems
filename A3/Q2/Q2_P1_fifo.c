#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define fifo1 "Q2_FIFO1"
#define fifo2 "Q2_FIFO2"

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
	
	mkfifo(fifo1,0666);
	mkfifo(fifo2,0666);
	
	char buffer[21];
	int i=0;
	for (;i<50;){
		int f1 = open(fifo1,O_WRONLY);
		for (int j=i;j<i+5;j++){
			if (write(f1,sentence[j],21)==-1){
				perror("Cannot write");
			}
		}
		close(f1);
		
		int f2=open(fifo2,O_RDONLY);
		if (read(f2,buffer,sizeof(buffer))==-1){
			perror("Cannot read");
		}
		close(f2);
		
		buffer[20]=0;
		int ans = atoi(buffer);
		printf("%d\n",ans);
		if (ans==i+4){
			i=ans+1;
		}
		else{
			perror("Wrong ack recieved");
		}
	}
	clock_gettime(CLOCK_REALTIME,&end);
	long sec = end.tv_sec-start.tv_sec;
	long nsec = end.tv_nsec-start.tv_nsec;
	double final = sec + nsec*1e-9;
	printf("Time measured: %.9f seconds.\n",final);
	exit(EXIT_SUCCESS);
}
