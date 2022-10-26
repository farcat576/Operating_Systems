#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*cat argv[1]*/
/*cat*/

int main(int argc,char** argv){
	int check=0;
	char* current = NULL;
	size_t length=100;
	char* change="-";
	FILE *file_ptr;
	
	int i=1;
	while(argv[i]!=NULL){
		if (strcmp(argv[i],change)==0){
			while(1){
				if (getline(&current,&length,stdin)==-1){
					break;
				}
				printf("%s",current);
			}
		}
		else{
			file_ptr = fopen(argv[i],"r");
			if (file_ptr==NULL){
				check=1;
				break;
			}
			while(getline(&current,&length,file_ptr)>0){
				printf("%s",current);
			}
			fclose(file_ptr);
		}
		i++;
	}
	
	if (i==1){
		while(1){
			if (getline(&current,&length,stdin)==-1){
				break;
			}
			printf("%s",current);
		}
	}
	
	if (check==1){
		printf("Error occured\n");
	}
	return check;
}
