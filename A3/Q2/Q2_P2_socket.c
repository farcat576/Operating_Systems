#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

#define SOCKET_PATH "Q2_SOCKET"

int main(){
	struct sockaddr_un addr;
	int P2 = socket(AF_UNIX,SOCK_SEQPACKET,0);
	if (P2<0){
		perror("Couldn't create datagram socket");
	}
		
	memset(&addr,0,sizeof(addr));
	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path,SOCKET_PATH,sizeof(addr.sun_path)-1);
	if (bind(P2,(const struct sockaddr *)&addr,sizeof(addr))<0){
		perror("Unable to bind");
	}
	if (listen(P2,10)<0){
		perror("Unable to listen");
	}
	
	char buffer[21];
	int i=0;
	int P1=accept(P2,NULL,NULL);
	if (P1==-1){
		perror("Unable to accept");
	}
	for (;i<50;){
		int j;
		sleep(2);
		for (j=i;j<i+5;j++){
			if (read(P1,buffer,sizeof(buffer))==-1){
				perror("Cannot read");
			}
			printf("%s\n",buffer);
		}
		
		sprintf(buffer, "%d", j-1);
		if (write(P1,buffer,sizeof(buffer))==-1){
			perror("Cannot read");
		}
		i=j;
	}
	exit(EXIT_SUCCESS);
}
