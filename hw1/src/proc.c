#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

#include "proc.h"
#include "list.h"

#define PATH "/proc/"
#define CMDLINE "/cmdline"
#define PROC_NAME "/comm"

	
struct list *addPID(){
	struct list *pList = newList();
	struct stat file_state;
	DIR *dir_pid;
	struct dirent *dp;

	if ((dir_pid = opendir(PATH)) == NULL){
		puts("Failed in open /proc/ !\n");
		exit(-1);
	}

	while((dp = readdir(dir_pid)) != NULL){
		lstat(dp->d_name, &file_state);
		if(!strcmp(".", dp->d_name) || !strcmp("..", dp->d_name)){
			continue;
		}
		else if(S_ISDIR(file_state.st_mode) && isdigit(*(dp->d_name))){
			pList->process->pid = dp->d_name;
			append(pList);
			addCMD(pList, pList->process->pid);
			addName(pList, pList->process->pid);
			addInode(pList, pList->process->pid);
			pList = pList->lNext;
		}
	}
	closedir(dir_pid);

	return pList;
}

void addCMD(struct list* lHead, char *pid){
	char path[40] = PATH;
	char tmp[256];
	while(lHead != NULL){
		if(!strcmp(lHead->process->pid, pid)){
			strcat(path, pid);
			strcat(path, CMDLINE);
			FILE *cmd = fopen(path, "r");
			fread(tmp, 256, 1, cmd);
			fclose(cmd);
			
			char* ptr= strtok(tmp, "\0");
			strcpy(lHead->process->cmdline, ptr);
		}
		else lHead = lHead->lNext;
	}
}

void addName(struct list* lHead, char *pid){
	char path[40] = PATH;
	while(lHead != NULL){
		if(!strcmp(lHead->process->pid, pid)){
			strcat(path, pid);
			strcat(path, PROC_NAME);
			FILE *name = fopen(path, "r");
			fread(lHead->process->processName, 1024, 1, name);
			fclose(name);
		}
		else lHead = lHead->lNext;
	}
}

void addInode(struct list *lHead, char *pid){
	char path[40] = PATH;
	while(lHead != NULL){
		if(!strcmp(lHead->process->pid, pid)){
			strcat(path, pid);
			strcat(path,"fd/");
			DIR *dir = opendir(path);
			struct dirent *dp;
			if(dir == NULL) break;
			while(dp = readdir(dir)!=NULL){
				if(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
					strcat(path, dp->d_name);
					char message[256];
					readlink(path, message, 256);
					char* ptr = strtok(message, ":");
					if(!strcmp(ptr, "socket")){
						ptr = strtok(NULL, "\0");
						char *r = strtok(ptr, "[");
						lHead->process->i->inode = (int)strtol(r, NULL, 10);
						lHead->process->i->fd = (int)strtol(dp->d_name, NULL, 10);
						nodeAppend(lHead->process->i);
					}
				}
			}
			closedir(dir);
		}
		else lHead = lHead->lNext;
	}
}

node *nodeSearch(struct node *nHead, long inode){
	while(nHead != NULL){
		if(nHead->inode == inode){
			return nHead;
		}
		else nHead = nHead->nNext;
	}

	return nHead;
}

char *split(char* string, int base, int tail){
	int len = tail - base;
	char *subset = (char*)malloc(sizeof(char)*len);
	for(int i = 0; i < strlen(string); i++){
		strncpy(subset, string + base, len);
	}
	return subset;
}
