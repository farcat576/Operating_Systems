#include <stdio.h>
#include <unistd.h>

/*rm argv[1]*/

int main(int argc,char** argv){
	int status=0;
	int i=1;
	while(status==0 && argv[i]!=NULL){
		status=remove(argv[i]);
		i++;
	}
	if (status!=0){
		printf("File could not be deleted\n");
	}
	return status;
}
