#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <dlfcn.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *base = "./";
	char ld_preload[] = "LD_PRELOAD=";
    char *sandboxlib = "./sandbox.so";
    int opt, start = 0;

	if(argc < 2){
		printf("usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]\n");
		printf("-p: The path to sandbox.so, default is ./sandbox.so\n");
        printf("-d: The working directory.\n");
        printf("--: The executed command to terminal.\n");

		exit(-1);

	}

    while((opt = getopt(argc, argv, ":dp")) != -1){

		if(opt == 'd'){
            base = argv[optind];
			printf("%s\n", base);
            start += 1;
		}
		
		else if (opt == 'p'){
            sandboxlib = argv[optind];
            start += 1;
		}

		else{
			printf("Unknown command.\n");
			return 0;
		}
    }
	
    char command[1024] = "";

    for(int i = optind + start; i < argc; i++) {

		if(!strcmp(argv[i], "--")){
			i ++;
		}
		else{
			strncat(command, argv[i], strlen(argv[i]));
			strncat(command, " ", strlen(" "));
		}
	}

	char* real = realpath(sandboxlib, NULL);
	if(real == NULL){
		printf("Unknown %s path.\n", sandboxlib);
		exit(-1);
	}
	char* full= (char*)malloc(sizeof(char)*1024);
	strcat(full, ld_preload);
	strcat(full, real);
	strcat(full, " ");
	strcat(full, command);
	strcat(full, " ");
	printf("%s\n", full);

	chdir(base);
    system(full);
    return 0;
}
