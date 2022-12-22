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

int main(){
	mkfifo(fifo1,0666);
	mkfifo(fifo2,0666);
	
	char buffer[21];
	int i=0;
	for (;i<50;){
		int j;
		int f1 = open(fifo1,O_RDONLY);
		for (j=i;j<i+5;j++){
			if (read(f1,buffer,sizeof(buffer))==-1){
				perror("Cannot read");
			}
			printf("%s\n",buffer);
		}
		close(f1);
		
		int f2=open(fifo2,O_WRONLY);
		sprintf(buffer, "%d", j-1);
		if (write(f2,buffer,sizeof(buffer))==-1){
			perror("Cannot read");
		}
		close(f2);
		i=j;
	}
	exit(EXIT_SUCCESS);
}
