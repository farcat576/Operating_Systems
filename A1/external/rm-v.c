#include <stdio.h>
#include <unistd.h>

/*rm -v argv[2]*/

int main(int argc,char** argv){
	int status=0;
	int i=2;
	while(status==0 && argv[i]!=NULL){
		status=remove(argv[i]);
		if (status==0){
			printf("removed '");
			printf("%s",argv[2]);
			printf("'\n");
		}
		i++;
	}
	if (status!=0){
		printf("File could not be deleted\n");
	}
	return status;
}
