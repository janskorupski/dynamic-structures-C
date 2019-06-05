#include <stdlib.h> 
#include <stdio.h>

typedef struct Slot_noptr{
	int value;
	struct Slot_noptr* right;
	//struct Slot* left;
	//struct Slot* up;
	struct Slot_noptr* down;
	}Slot_noptr, *Slot; //Mtx, head
	
typedef struct Matrix_noptr{
	int size;
	Slot first;
	}Matrix_noptr, *Matrix;//Mtxhead

Matrix Matrix_innit()
	{
		Matrix h = (Matrix)malloc(sizeof(Matrix_noptr));
		h->first=NULL;
		h->size=-1;
		return h;
	}
	
Slot Slot_new()
	{
		Slot h = (Slot)malloc(sizeof(Slot_noptr));
		h->down=NULL;
		//h->left=NULL;
		h->right=NULL;
		//h->up=NULL;
		h->value=0;
		return h;
	}
	
Slot Matrix_get_Slot(int i, int j, Matrix h) //funtion that returns the pointer to the element of i'th row and j'th column of the h matrix (first column is no. 0)
	{
		if (i>h->size || j>h->size)
			{
				printf("\nerror: matrix index too big\n");
				return NULL;
			}
		//else:
		Slot ptr = h->first;
		int k;
		for(k=0;k<i;k++)
		{
			ptr = ptr->down;
		}
		for(k=0;k<j;k++)
		{
			ptr = ptr->right;
		}
		return ptr;
	}	
	
void Matrix_enlarge(Matrix h)
	{
	if((*h).size==-1)
		{
			(*h).first=Slot_new();
			h->size++;
		}
	else if((*h).size>0)
		{
			int size = h->size;
			Slot ptr;//ptr stands for pointer
			
			//FIRST LETS ADD A NEW COLUMN:
			ptr=Matrix_get_Slot(0,size,h);//I set ptr to the upper right element of the matrix
			
			ptr->right=Slot_new();//first I add a new slot to the right, because:
			while(ptr->down!=NULL)//here I will work one step downwards, so I add a new slot to the right of the slot beneath the ptr, so that I can add a ptr->rigth->down value
			{
				ptr->down->right=Slot_new();
				ptr->right->down=ptr->down->right;
				ptr=ptr->down;
			}
			
			//NOW LETS ADD A NEW ROW:
			ptr = Matrix_get_Slot(size,0,h);//I set the ptr to the 1st column, last row
			
			ptr->down=Slot_new();
			while(ptr->right!=NULL)
			{
				ptr->right->down=Slot_new();
				ptr->down->right=ptr->right->down;
				ptr=ptr->right;
			}
				
			(*h).size++;
		}
		else
		{
			h->first->right=Slot_new();
			h->first->down=Slot_new();
			h->first->down->right=Slot_new();
			h->first->right->down=h->first->down->right;
			(*h).size++;
		}
	}
	
void Matrix_print(Matrix h)
	{
		printf("\n");
		Slot ptr = (*h).first;
		while(ptr!=NULL)
		{
			Slot ptr2 = ptr->right;
			printf("%d ",ptr->value);
			while(ptr2!=NULL)
			{
				printf("%d ",ptr2->value);
				ptr2 = ptr2->right;
			}
			ptr=ptr->down;
			printf("\n");
		}
		printf("\n");
	}
	
void working_Matrix_print(Matrix h)//used only for bug-fixing
{
	Slot ptr = (*h).first;
	while(ptr!=NULL)
	{
		Slot ptr2 = ptr->right;
		printf("	id:%d, value:%d, down:%d, right:%d,	",ptr,ptr->value,ptr->down,ptr->right);
		while(ptr2!=NULL)
		{
			printf("	id:%d, value:%d, down:%d, right:%d,	",ptr2,ptr2->value,ptr2->down,ptr2->right);
			ptr2 = ptr2->right;
		}
		ptr=ptr->down;
		printf("\n");
	}
}

void Matrix_put(int val, int i, int j, Matrix h)
{
	Slot ptr = Matrix_get_Slot(i, j, h);
	if(ptr==NULL)
		printf("error! could not put value\n");
	else
		ptr->value=val;
}

int Matrix_get(int i, int j, Matrix h)
{
	Slot ptr = Matrix_get_Slot(i, j, h);
	if (ptr==NULL)
		{
			printf("error! could not get value!\n");
			return 0;
		}
	return ptr->value;
}
	
		

