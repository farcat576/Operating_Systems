#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/*date -R*/

int main(int argc,char** argv){
	time_t t;
	struct tm* current;
	char output[200];
	char* week[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	char* month[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	
	time(&t);
	current = localtime(&t);
	if (argc>2){
		printf("Too many arguments\n");
	}
	else if (strftime(output,sizeof(output),"%a, %0d %b %Y %2H:%2M:%2S %z",current)==0){
		printf("Error has occured\n");
	}
	else{
		printf("%s\n",output);
	}
}
