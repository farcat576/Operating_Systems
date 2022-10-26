#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*mkdir -m (num) argv[3]*/

int main(int argc,char** argv){
	int check=0;
	int i=3;
	while(check==0 && argv[i]!=NULL){
		int check = mkdir(argv[i],0);
		int mode = strtol(argv[2],0,8);
		if (check==0){
			if (chmod(argv[3],mode)!=0){
				printf("Directory mode could not be updated\n");
			}
		}
		else{
			printf("Directory could not be created\n");
		}
		i++;
	}
	return check;
}
