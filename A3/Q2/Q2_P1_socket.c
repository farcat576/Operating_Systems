#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

#define SOCKET_PATH "Q2_SOCKET"

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
	
	struct sockaddr_un addr;
	int P1 = socket(AF_UNIX,SOCK_SEQPACKET,0);
	if (P1<0){
		perror("Couldn't create datagram socket");
	}
	
	memset(&addr,0,sizeof(addr));
	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path,SOCKET_PATH,sizeof(addr.sun_path)-1);
	if (connect(P1,(const struct sockaddr *)&addr,sizeof(addr))<0){
		perror("Unable to connect");
	}
	
	char buffer[21];
	int i=0;
	for (;i<50;){
		for (int j=i;j<i+5;j++){
			if (write(P1,sentence[j],21)==-1){
				perror("Cannot write");
			}
		}
		
		sleep(1);
		if (read(P1,buffer,sizeof(buffer))==-1){
			perror("Cannot read");
		}
		
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
	double final=sec+nsec*1e-9;
	printf("Time measured: %.9f seconds.\n",final);
	exit(EXIT_SUCCESS);
}
