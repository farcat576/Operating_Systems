#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*mkdir argv[1]*/

int main(int argc,char** argv){
	int check=0;
	int i=1;
	while(check==0 && argv[i]!=NULL){
		check = mkdir(argv[i],0);
		i++;
	}
	if (check!=0){
		printf("Directory could not be created\n");
	}
	return check;
}
