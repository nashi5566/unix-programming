#include<stdio.h>
#include<stdlib.h>

#include "list.h"

list *append(list *l, void *data){
	node *n = (node*)malloc(sizeof(node));
	n->data = data;
	if(l->lHead == NULL) {
		l->lHead = n;
		l->lend = n;
	}
	else{
		l->lend->next = n;
		l->lend = n;
	}

	l->len ++;

	return l;
}

node *search(list *l, void *data){
	while(l->lHead != NULL){
		if(data == l->lHead->data){
			return l->lHead;
		}
		
		l->lHead = l->lHead->next;
	}

	return NULL;
}
