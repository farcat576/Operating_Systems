#include <stdio.h>
#include <unistd.h>

/*rm -f argv[2]*/

int main(int argc,char** argv){
	int status=0;
	int i=2;
	while(status==0 && argv[i]!=NULL){
		status=remove(argv[i]);
		i++;
	}
	return status;
}
