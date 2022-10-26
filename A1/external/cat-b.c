#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*cat -b argv[2]*/
/*cat -b*/

int main(int argc,char** argv){
	int check=0;
	char *current = NULL;
	size_t length =100;
	FILE *file_ptr;
	int line=1;
	char* change="-";
	char* compar = "\n";
	
	int i=2;
	while(argv[i]!=NULL){
		if (strcmp(argv[i],change)==0){
			while(1){
				if (getline(&current,&length,stdin)==-1){
					check=1;
					break;
				}
				if(strcmp(compar,current)==0){
					printf("%s",current);
				}
				else{
					printf("    %d  %s",line,current);
					line++;
				}
			}
		}
		else{
			file_ptr = fopen(argv[i],"r");
			if (file_ptr==NULL){
				check=1;
				break;
			}
			while(getline(&current,&length,file_ptr)>0){
				if(strcmp(compar,current)==0){
					printf("%s",current);
				}
				else{
					printf("    %d  %s",line,current);
					line++;
				}
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
			if(strcmp(compar,current)==0){
				printf("%s",current);
			}
			else{
				printf("    %d  %s",line,current);
				line++;
			}
		}
	}
	
	if (check==1){
		printf("Error occured\n");
	}
	return check;
}
