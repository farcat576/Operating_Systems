#include <stdio.h>
#include <string.h>
#include <dirent.h>

/*ls -a argv[2]*/
/*ls -a*/

int main(int argc,char** argv){
	struct dirent *d;
	
	int i=2;
	while (argv[i]!=NULL){
			DIR *dh = opendir(argv[i]);
			if (dh==NULL){
				printf("Directory not found\n");
				i++;
				break;
			}
			do{
				d=readdir(dh);
				if (d==NULL) break;
				printf("%s\n",d->d_name);
			} while (1);
		i++;
	}
	if(i==2){
		DIR *dh = opendir(".");
		do{
			d=readdir(dh);
			if (d==NULL) break;
			printf("%s\n",d->d_name);
		} while (1);
	}
}
