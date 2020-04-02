#ifndef __LIST_H
#define __LIST_H

typedef struct list {
	struct node *lHead;
	struct node *lend;
	size_t len;
} list;

typedef struct node {
	struct node* next;
	void *data;
} node;

list *append(list *l, void *data);
node *search(list *lhead, void *data);

#endif
