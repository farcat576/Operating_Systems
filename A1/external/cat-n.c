#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*cat -n argv[2]*/
/*cat -n*/

int main(int argc,char** argv){
	int check=0;
	char *current = NULL;
	size_t length =100;
	FILE *file_ptr;
	int line=1;
	char* change="-";
	
	int i=2;
	while(argv[i]!=NULL){
		if (strcmp(change,argv[i])==0){
			while(1){
				if (getline(&current,&length,stdin)==-1){
					check=1;
					break;
				}
				printf("    %d  %s",line,current);
				line++;
			}
		}
		else{
			file_ptr = fopen(argv[i],"r");
			if (file_ptr==NULL){
				check=1;
				break;
			}
			while(getline(&current,&length,file_ptr)>0){
				printf("    %d  %s",line,current);
				line++;
			}
			fclose(file_ptr);
		}
		i++;
	}
	
	if (i==2){
		while(1){
			if (getline(&current,&length,stdin)==-1){
				check=1;
				break;
			}
			printf("    %d  %s",line,current);
			line++;
		}
	}
	
	if (check==1){
		printf("Error occured\n");
	}
	return check;
}
