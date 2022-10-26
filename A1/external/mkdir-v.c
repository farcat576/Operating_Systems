#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*mkdir -v argv[2]*/

int main(int argc,char** argv){
	int check=0;
	int i=2;
	while(check==0 && argv[i]!=NULL){
		check = mkdir(argv[2],0);
		if (check==0){
			chmod(argv[2],0777);
			printf("mkdir: created directory '");
			printf("%s",argv[2]);
			printf("'\n");
		}
		else{
			printf("Directory could not be created\n");
		}
		i++;
	}
	return check;
}
