#include <stdlib.h> 
#include <stdio.h>


typedef struct list_element{
	struct list_element* next;
	struct list_element* prev;
	int val;	
	int num;
}list_element, *list;

list list_innit()//the head of the list
{
	list l = (list)malloc(sizeof(list_element));
	l->val=-1; // the value of the head will be the number of the elements in the list
	l->num=-1;
	l->next=l;//next will be the first one
	l->prev=l;//prev will be the last one
}

void list_push(int val, list h)
{
	list new_el = (list)malloc(sizeof(list_element));
	new_el->prev=h->prev;
	new_el->next=h;
	h->prev->next=new_el;
	h->prev=new_el;
	new_el->num=new_el->prev->num+1;
	new_el->val=val;
	h->val++;
}

void list_push_back(int val, list h)
{
	list new_el = (list)malloc(sizeof(list_element));
	new_el->next=h->next;
	new_el->prev=h;
	h->next->prev=new_el;
	h->next=new_el;
	
	new_el->val=val;
	new_el->num=0;
	
	list ptr=new_el->next;
	while(ptr!=h)
	{
		ptr->num=ptr->prev->num+1;
		ptr=ptr->next;
	}
	
	h->val++;
}

int list_isempty(list h)
{
	return (h->next==h);
}

void list_remove_node(list ptr)
{
	if(ptr->num!=-1)
	{
		list prev=ptr->prev;
		list next=ptr->next;
		prev->next=next;
		next->prev=prev;
		free(ptr);
	}
	else
		printf("error! trying to remove list head!\n");
}

int list_get(int i, list h)
{
	if(i<0||i>h->val)
	{
		printf("error, index out of range!\n");
		return 0;
	}
	//else:
	int num;
	list ptr=h->next;
	
	while(ptr->num!=i&&ptr!=h)
		ptr = ptr->next;
	
	if(ptr==h)
		printf("error, some big fuckkin error #1, idk what happend lol xdd\n");
	else
		return ptr->val;
		
	return 0;
}

void list_print(list h)
{
	if(list_isempty(h))
		printf("[]\n");
	else
	{
		list ptr=h->next;
		printf("[");
		while(ptr!=h->prev) 
		{
			printf("%d,",ptr->val);
			ptr=ptr->next;
		}
		printf("%d]\n", ptr->val);
	}
}

list list_copy(list oryg)
{
	list copy = list_innit();
	list ptr = oryg->next;
	while(ptr!=oryg)
	{
		list_push(ptr->val,copy);
		ptr=ptr->next;
	}
}

void list_print_working(list h)
{

	list ptr=h;			
	printf("[val ] [   %d   ]",ptr->val);
	ptr=ptr->next;
	while(ptr!=h) 
	{
		printf(" [   %d   ]",ptr->val);
		ptr=ptr->next;
	}
	printf("\n");
	
	ptr=h;			
	printf("[self] [%d]",ptr);
	ptr=ptr->next;
	while(ptr!=h) 
	{
		printf(" [%d]",ptr);
		ptr=ptr->next;
	}
	printf("\n");
	
	ptr=h;			
	printf("[next] [%d]",ptr->next);
	ptr=ptr->next;
	while(ptr!=h) 
	{
		printf(" [%d]",ptr->next);
		ptr=ptr->next;
	}
	printf("\n");
	
	ptr=h;			
	printf("[prev] [%d]",ptr->prev);
	ptr=ptr->next;
	while(ptr!=h) 
	{
		printf(" [%d]",ptr->prev);
		ptr=ptr->next;
	}
	printf("\n");
	
	ptr=h;			
	printf("[num] [   %d   ]",ptr->num);
	ptr=ptr->next;
	while(ptr!=h) 
	{
		printf(" [   %d   ]",ptr->num);
		ptr=ptr->next;
	}
	printf("\n");

}

