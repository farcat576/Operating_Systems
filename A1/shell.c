#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>

char* reader(){ //Takes one line inputs
	char* line=NULL;
	size_t size=0;
	if(getline(&line,&size,stdin)==-1){
		printf("Error in allocating input space\n");
	}
	return line;
}

char** splitter(char* line){ //Splits one line input into char**
	int size=64;
	int position=0;
	char **tokens = (char **) malloc(size*sizeof(char*));
	char *delim = " \t\r\n\a";
	if (tokens==NULL){
		printf("Error in allocating input space\n");
	}
	
	char *token=strtok(line,delim);
	while(token != NULL){
		tokens[position]=token;
		position++;
		
		if(position>=size){
			size+=64;
			char** backup=tokens;
			tokens=realloc(tokens,size*sizeof(char*));
			if (tokens==NULL){
				free(backup);
				printf("Error in allocating input space\n");
			}
		}
		token=strtok(NULL,delim);
	}
	tokens[position]=NULL;
	return tokens;
}

int counter(char* argv[]){ // Counts argc
	int count=0;
	while(argv[count]!=NULL){
		count++;
	}
	return count;
}

int fork_exec(int argc,char *argv[]){ //fork() and exec()
	pid_t pid;
	int status;
	
	pid=fork();
	if (pid>0){
		wait(NULL);
	}
	else if(pid==0){
		if (execve(argv[0],argv,NULL)==-1){
			perror("Could not use execvp");
		}
		abort();
	}
	else{
		perror("Error while forking");
	}
	return 0;
}

void *execute(void *arg){ //system()
	char** argv = (char**) arg;
	char *command=malloc(160*sizeof(char));
	strcpy(command,argv[0]);
	int i=1;
	while(strcmp(argv[i],"&t")!=0){
		strcat(command," ");
		strcat(command,argv[i]);
		i++;
	}
	system(command);
}

int thread_exec(int argc,char *argv[]){ //pthread_create() and pthread_join()
	pthread_t thread1;
	if (pthread_create(&thread1,NULL,execute,(void *) argv) != 0){
		perror("Failed to create a thread");
		return 1;
	}
	if (pthread_join(thread1,NULL) != 0){
		perror("Failed to create a thread");
		return 1;
	}
	return 0;
}

int parse(char* start,int argc,char* argv[]){ //Parse char** and send to respective execution methods
	char *c[]={"echo","cd","pwd","cat","date","ls","mkdir","rm"};
	char *opt[]={"-P","-L","-n","-help","-b","-u","-R","-a","-A","-m","-v","-f"};
	int status;
	int fork=0;
	int thread=0;
	
	//Fixing the pwd of absolute address
	char* root=(char *) malloc(160*sizeof(char));
	strcpy(root,start);
	
	//Internal commands
	if (argc==0) return 1;
	if (strcmp(argv[0],c[0])==0){
		if (argv[1]==NULL) printf("\n");
		else if (strcmp(argv[1],opt[2])==0){
			int i=2;
			for (;argv[i+1]!=NULL;i++) printf("%s ",argv[i]);
			printf("%s",argv[i]);
		}
		else if (strcmp(argv[1],opt[3])==0){
			char* mesg[]={"Usage: /bin/echo [SHORT-OPTION]... [STRING]...",
"  or:  /bin/echo LONG-OPTION",
"Echo the STRING(s) to standard output.",
"",
"  -n             do not output the trailing newline",
"  -e             enable interpretation of backslash escapes",
"  -E             disable interpretation of backslash escapes (default)",
"      --help     display this help and exit",
"      --version  output version information and exit",
"",
"If -e is in effect, the following sequences are recognized:",
"",
"  \\\\      backslash",
"  \\a      alert (BEL)",
"  \\b      backspace",
"  \\c      produce no further output",
"  \\e      escape",
"  \\f      form feed",
"  \\n      new line",
"  \\r      carriage return",
"  \\t      horizontal tab",
"  \\v      vertical tab",
"  \\0NNN   byte with octal value NNN (1 to 3 digits)",
"  \\xHH    byte with hexadecimal value HH (1 to 2 digits)",
"",
"NOTE: your shell may have its own version of echo, which usually supersedes",
"the version described here.  Please refer to your shell's documentation",
"for details about the options it supports.",
"",
"GNU coreutils online help: <https://www.gnu.org/software/coreutils/>",
"Full documentation at: <https://www.gnu.org/software/coreutils/echo>",
"or available locally via: info '(coreutils) echo invocation'",NULL};
			int i=0;
			while(mesg[i]!=NULL){
				printf("%s\n",mesg[i]);
				i++;
			}
		}
		else{
			for (int i=1;argv[i]!=NULL;i++){
				printf("%s ",argv[i]);
			}
			printf("\n");
		}
	}
	else if (strcmp(argv[0],c[1])==0){
		if (argv[1]==NULL){
			status = chdir(getenv("HOME"));
		}
		else if(strcmp(argv[1],opt[0])==0){
			if (argv[2]==NULL){
				status = chdir(getenv("HOME"));
			}
			else{
				status = chdir(argv[2]);
				status = chdir(getenv("PWD"));
			}
		}
		else{
			status = chdir(argv[1]);
		}
		if (status==1) printf("Error in cd\n");
	}
	else if (strcmp(argv[0],c[2])==0){
		if (argv[1]==NULL){
			char cwd[256];
			int status=1;
			if (getcwd(cwd,sizeof(cwd))!=NULL){
				printf("%s\n",cwd);
			}
			else{
				printf("Error in pwd\n");
			}
		}
		else if (strcmp(argv[1],opt[1])==0){
			char cwd[256];
			int status=1;
			if (getcwd(cwd,sizeof(cwd))!=NULL){
				printf("%s\n",getenv("PWD"));
			}
			else{
				printf("Error in pwd\n");
			}
		}
		else printf("Error in pwd\n");
	}
	
	//External commands
	else if (strcmp(argv[0],c[3])==0){
		if (argv[1]==NULL) argv[0]=strcat(root,"/cat.o");
		else if (strcmp(argv[1],opt[2])==0) argv[0]=strcat(root,"/cat-n.o");
		else if (strcmp(argv[1],opt[4])==0) argv[0]=strcat(root,"/cat-b.o");
		else argv[0]=strcat(root,"/cat.o");
		if (strcmp(argv[argc-1],"&t")!=0){
			fork=1;
		}
		else{
			thread=1;
		}
	}
	else if (strcmp(argv[0],c[4])==0){
		if (argv[1]==NULL) argv[0]=strcat(root,"/date.o");
		else if (strcmp(argv[1],opt[5])==0) argv[0]=strcat(root,"/date-u.o");
		else if (strcmp(argv[1],opt[6])==0) argv[0]=strcat(root,"/date-R.o");
		else argv[0]=strcat(root,"/date.o");
		if (strcmp(argv[argc-1],"&t")!=0){
			fork=1;
		}
		else{
			thread=1;
		}
	}
	else if (strcmp(argv[0],c[5])==0){
		if (argv[1]==NULL) argv[0]=strcat(root,"/ls.o");
		else if (strcmp(argv[1],opt[7])==0) argv[0]=strcat(root,"/ls-a.o");
		else if (strcmp(argv[1],opt[8])==0) argv[0]=strcat(root,"/ls-A.o");
		else argv[0]=strcat(root,"/ls.o");
		if (strcmp(argv[argc-1],"&t")!=0){
			fork=1;
		}
		else{
			thread=1;
		}
	}
	else if (strcmp(argv[0],c[6])==0){
		if (argv[1]==NULL) argv[0]=strcat(root,"/mkdir.o");
		else if (strcmp(argv[1],opt[9])==0) argv[0]=strcat(root,"/mkdir-m.o");
		else if (strcmp(argv[1],opt[10])==0) argv[0]=strcat(root,"/mkdir-v.o");
		else argv[0]=strcat(root,"/mkdir.o");
		if (strcmp(argv[argc-1],"&t")!=0){
			fork=1;
		}
		else{
			thread=1;
		}
	}
	else if (strcmp(argv[0],c[7])==0){
		if (argv[1]==NULL) argv[0]=strcat(root,"/rm.o");
		else if (strcmp(argv[1],opt[10])==0) argv[0]=strcat(root,"/rm-v.o");
		else if (strcmp(argv[1],opt[11])==0) argv[0]=strcat(root,"/rm-f.o");
		else argv[0]=strcat(root,"/rm.o");
		if (strcmp(argv[argc-1],"&t")!=0){
			fork=1;
		}
		else{
			thread=1;
		}
	}
	else{
		printf("Not a valid instruction\n");
	}
	
	//Final execution
	if (fork) status=fork_exec(argc,argv);
	if (thread) status=thread_exec(argc,argv);
	return status;
}

int main(){ //While loop to run entire shell
	char *line;
	char * root = getenv("PWD");
	int argc;
	char **argv;
	int status;
	do{
		printf("> ");
		line = reader();
		if (line==NULL) break;
		argv = splitter(line);
		if (argv==NULL) break;
		argc = counter(argv);
		status = parse(root,argc,argv);
	} while(status==0);
}
