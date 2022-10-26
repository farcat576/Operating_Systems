#include <stdio.h>
#include <string.h>
#include <dirent.h>

/*ls -A argv[2]*/
/*ls -A*/

int main(int argc,char** argv){
	struct dirent *d;
	char *compar="-";
	char *ignore_1=".";
	char *ignore_2="..";
	
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
				if(strcmp(d->d_name,ignore_1)==0) continue;
				if(strcmp(d->d_name,ignore_2)==0) continue;
				printf("%s\n",d->d_name);
			} while (1);
		i++;
	}
	if(i==2){
		DIR *dh = opendir(".");
		do{
			d=readdir(dh);
			if (d==NULL) break;
			if(strcmp(d->d_name,ignore_1)==0) continue;
			if(strcmp(d->d_name,ignore_2)==0) continue;
			printf("%s\n",d->d_name);
		} while (1);
	}
}
