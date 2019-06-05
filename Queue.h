#include <stdio.h>
#include <stdlib.h>

typedef struct Queue_noptr{//noptr stands for not a pointer, since I will be using mostly pointers its easier for me that way
	int val;
	struct Queue_noptr* next;
}Queue_noptr,*Queue;

Queue Queue_innit()
{
	Queue q = (Queue)malloc(sizeof(Queue_noptr));
	q->next=NULL;
	q->val=-1;//as it is a queue implementation with a head, the head value will keep the number of elements in the queue, starting with 0. Idk, might be usefull at some point and it doesn't cost much i think
	return q;
}

void Queue_push(int val, Queue head)
{
	Queue ptr = head;
	while(ptr->next!=NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = (Queue)malloc(sizeof(Queue_noptr));
	ptr->next->val=val;
	ptr->next->next=NULL;
	head->val++;
}

int Queue_pop(Queue head)
{
	if (head->next==NULL)
	{
		printf("the queue has ended, cannot pop\n");
		return 0;
	}
	int val = head->next->val;
	Queue ptr1 = head->next->next;
	free(head->next);
	head->next = ptr1;
	head->val--;
	return val;
}

int Queue_isempty(Queue head)
{
	return(head->next==NULL);
}

