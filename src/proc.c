#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>

#include "list.h"
#include "proc.h"

#define PATH "/proc/"
#define CMDLINE "/cmdline"
#define PROC_NAME "/comm"

list *findallpid(list *l){
	DIR *dir;
	struct dirent *dp;
	dir = opendir(PATH);
	if(dir == NULL) exit(-1);
	while(dp = readdir(dir)){
		if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) continue;
		else if(isdigit(dp->d_name[0])){
			process *p = (process*)malloc(sizeof(process));
			p->pid = strtol(dp->d_name, NULL, 10);
			l = append(l, p);
		}
	}

	closedir(dir);

	return l;
}

node *pidfindprocess(list *l, long pid){
	while(l != NULL){
		if(((process*)(l->lHead->data))->pid == pid){
			return l->lHead;
		}
		else l->lHead = l->lHead->next;
	}
	
	puts("Process isn't in the list.\n'");
	return NULL;
}

void addCMD(list* lHead, long pid){
	char path[60] = PATH;
	char tmp[256];
	
	strcpy(path, PATH);
	node *n = pidfindprocess(lHead, pid);
	char p[20];
	sprintf(p, "%ld", pid);
	strcat(path, p);
	strcat(path, CMDLINE);

	FILE *f = fopen(path, "r");
	fread(tmp, 256, 1, f);
	fclose(f);

	char* ptr = strtok(tmp, "\0");
	if(ptr != NULL){
		strcpy(((process*)n->data)->cmdline, ptr);
	}

}

void addName(list* lHead, long pid){
	char path[40] = PATH;
	char tmp[256];
	node *n = pidfindprocess(lHead, pid);
	char p[20];
	sprintf(p, "%ld", pid);
	strcat(path, p);
	strcat(path,PROC_NAME);
	FILE *f = fopen(path, "r");
	fread(tmp, 256, 1, f);
	fclose(f);
	char *ptr= strtok(tmp, "\n");
	strcpy(((process*)n->data)->name, ptr);
}

list *findsocketinode(list *inodelist, long pid){
	if(inodelist->lHead == NULL) printf("yes\n");
	char path[60];
	DIR *dir;
	struct dirent *dp;
	strcpy(path, PATH);
	char *pt = (char*)malloc(sizeof(char)*20);
	sprintf(pt, "%ld", pid);
	strcat(path, pt);
	strcat(path, "/fd/");
	dir = opendir(path);
	while((dp = readdir(dir))){
		if(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
			strcat(path, dp->d_name);
			char message[256];
			readlink(path, message, 256);

			memset(path, 0, sizeof(path));
			strcpy(path, PATH);
			strcat(path, pt);
			strcat(path, "/fd/");
			message[strlen(message)] = '\0';
			
			if(strstr(message, "socket")){
				inode *i = (inode*)malloc(sizeof(inode));
				char* ptr = strtok(message, "[");
				ptr = strtok(NULL, "]");
				strcpy(i->inode_num, ptr);
				i->pid = pid;
				append(inodelist, i);
				memset(message, 0, sizeof(message));
			}
			else continue;
		}

	}
	closedir(dir);
	printf("%ld\n", inodelist->len);
	return inodelist;
}

/**
void addInode(list *lHead, long pid){
	char path[40] = PATH;
	DIR *dir = opendir(path);
	struct dirent *dp;
	if(dir == NULL) exit(-1);
	while(dp = readdir(dir)!=NULL){
		if(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
			strcat(path, dp->d_name);
			char message[256]
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
/**
node *nodeSearch(node *nHead, long inode){
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

***********************/
