/* INCOMPLETO !!!!!! */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#define BUFS 100

void pathb(char*,char*);
void copy(int,int);
void one_arg_func(char*);

int main(int argc, char* argv[]){
	int fdw,fdr,i;
	char destString[BUFS],answer='y';
	if(argc <= 1){
		printf("Too few arguments\n");
	} else if(argc == 2){
		//printf("DBG: argv[1] => %s",argv[1]);
		fdr = open(argv[1],O_RDONLY);

		if(fdr<0){
			perror(argv[0]);
			exit(0);
		}

		printf("Insert destination path: ");
		scanf("%s",destString);
		pathb(argv[1],destString);
		fdw = open(destString,O_WRONLY|O_CREAT|O_EXCL,0644);

		if(fdw < 0){
			perror(argv[0]);
			printf("Override file ? [Y,N]\n");
			read(0,&answer,1);
			if(answer == 'y' || answer == 'Y'){
				fdw = open(destString,O_WRONLY|O_CREAT|O_TRUNC);
			} else {
				printf("Copy aborted\n");
				exit(0);
			}
		}
		copy(fdr,fdw);

	}
}


void pathb(char *source, char* dest){
	int i=0,index = 0,j=0;
	char filename[BUFS];
	while(source[i] != '\0'){
		if(source[i] == '/')
			index = i;
		i++;
	}

	if(i == 0){
		return ;
	} else {
		for(i=index;source[i] != '\0'; i++){
			filename[j] = source[i];
			j++;
		}
		filename[j] = '\0';
	}
	strcat(dest,"/");
	strcat(dest,filename);

}


void copy(int fdr, int fdw){
	int i;
	char buff[BUFS];
	while((i=read(fdr,buff,BUFS))>0){
		write(fdw,buff,i);
	}

}
