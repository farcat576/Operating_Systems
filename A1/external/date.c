#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/*date*/

int main(int argc,char** argv){
	time_t t;
	struct tm* current;
	char output[200];
	char* week[]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	char* month[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	
	time(&t);
	current = localtime(&t);
	if (argc>1){
		printf("Too many arguments\n");
	}
	else if (strftime(output,sizeof(output),"%A %0d %B %Y %2H:%2M:%2S %Z",current)==0){
		printf("Error has occured\n");
	}
	else{
		printf("%s\n",output);
	}
}
