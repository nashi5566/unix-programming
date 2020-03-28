#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>

#include "list.h"
#include "connect.h"
#include "proc.h"

char tmp[128] = {};

clist *newCList(){
	clist *c = (clist*)malloc(sizeof(clist));
	c->Connect = (struct connect*)malloc(sizeof(connect));
}

char *ip4(char* address){
	//char tmp[64];
	struct sockaddr_in sa;
	struct in_addr ip;
	ip.s_addr = (int)strtol(address, NULL, 16);
	sa.sin_family = AF_INET;
	sa.sin_addr = ip;
	inet_ntop(AF_INET, &(sa.sin_addr), tmp, INET_ADDRSTRLEN);
	return tmp;
}

char *ip6(char* address){
	//char tmp[128];
	struct sockaddr_in6 sa;
	struct in6_addr ip;
	sa.sin6_family = AF_INET6;
	sa.sin6_addr = ip;

	char* raw = (char*)malloc(sizeof(char)*33);
	memset(raw, 0, 33);
	for(int i = 0; i < 4; i++){
		raw[6 + 8*i] = address[0 + 8*i];
		raw[7 + 8*i] = address[1 + 8*i];
		raw[4 + 8*i] = address[2 + 8*i];
		raw[5 + 8*i] = address[3 + 8*i];
		raw[2 + 8*i] = address[4 + 8*i];
		raw[3 + 8*i] = address[5 + 8*i];
		raw[0 + 8*i] = address[6 + 8*i];
		raw[1 + 8*i] = address[7 + 8*i];
	}

	for(int i = 0; i < 16; i ++){
		ip.s6_addr[i] = (int)strtol(split(raw, i*2, i*2+2), NULL, 16);
	}

	inet_ntop(AF_INET6, &(sa.sin6_addr), tmp, INET6_ADDRSTRLEN);
	free(raw);
	raw = NULL;
	return tmp;
}

clist *cappend(clist *c){
	c->lNext = newCList();
	c = c->lNext;
	c->lNext = NULL;

	return c;
}

struct connect *connectSearch(clist *cHead, long inode){
	while(cHead != NULL){
		if(cHead->Connect->inode == inode){
			return cHead->Connect;
		}
		else cHead = cHead->lNext;
	}
}


void parse(char* path, char* type, clist *c){
	FILE* f = fopen(path, "r");
	char* line = NULL;
	size_t buf_size = 0;
	ssize_t line_size;
	int count = 0;
	line_size = getline(&line, &buf_size, f);
	char *ptr;

	while(line_size >= 0){
		count ++;
		if(count == 1) continue;
		ptr = strtok(line, ":");
		ptr = strtok(NULL, ":");
		if (ptr != NULL){
			if(!strcmp(type, "ip4")){
				//c->Connect->local = ip4(ptr);
				strcpy(c->Connect->local, ip4(ptr));
			}
			else{ 
				//c->Connect->local = ip6(ptr);
				strcpy(c->Connect->local, ip6(ptr));
			}
		}

		ptr = strtok(NULL, " ");
		if(ptr != NULL){
			c->Connect->local_port = strtol(ptr, NULL, 16);
		}

		ptr = strtok(NULL, ":");
		if(ptr != NULL){
			if(!strcmp(type, "ip4")){
				//c->Connect->foregin = ip4(ptr);
				strcpy(c->Connect->foregin, ip4(ptr));
			}
			else{
			       //c->Connect->foregin = ip6(ptr);
			       strcpy(c->Connect->foregin, ip6(ptr)); 
			}
		}
		ptr = strtok(NULL, " ");
		if(ptr != NULL) c->Connect->fore_port = strtol(ptr, NULL, 16);
	
		ptr = strtok(NULL, " ");
		ptr = strtok(NULL, " ");
		ptr = strtok(NULL, " ");
		ptr = strtok(NULL, " ");
		ptr = strtok(NULL, " ");
		ptr = strtok(NULL, " ");
		ptr = strtok(NULL, " ");
		if(ptr != NULL) c->Connect->inode = strtol(ptr, NULL, 10);
		
		cappend(c);

		line_size = getline(&line, &buf_size, f);
	}
}
