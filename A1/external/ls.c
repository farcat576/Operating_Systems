#include <stdio.h>
#include <string.h>
#include <dirent.h>

/*ls argv[1]*/
/*ls*/

int main(int argc,char** argv){
	struct dirent *d;
	char *compar=".";
	
	int i=1;
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
				if(d->d_name[0]=='.') continue;
				printf("%s\n",d->d_name);
			} while (1);
		i++;
	}
	if(i==1){
		DIR *dh = opendir(".");
		do{
			d=readdir(dh);
			if (d==NULL) break;
			if(d->d_name[0]=='.') continue;
			printf("%s\n",d->d_name);
		} while (1);
	}
}
