#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Queue.h"
#include "List.h"
const int black = 1;
const int white = 0;
const int grey = 2;
const int yes=1;
const int no=0;


typedef struct Graph_noptr{
	Matrix links;
}Graph_noptr, *Graph;

void Graph_addnode(Graph g)
{
	Matrix_enlarge(g->links);
}

Graph Graph_innit(int size)
{
	Graph g = (Graph)malloc(sizeof(Graph_noptr));
	g->links = Matrix_innit();
	int i;
	for (i=0;i<=size;i++)
		Graph_addnode(g);
	return g;
}

void Graph_addlink(int from, int to, Graph g)
{
	Matrix_put(1,from,to,g->links);
}

void Graph_removelink(int from, int to, Graph g)
{
	Matrix_put(0,from,to,g->links);
}

void Graph_print(Graph g)
{
	Matrix_print(g->links);
}

list Graph_BFS(Graph g, int a, int b)//from a to b, so a is the source
{
	Queue q = Queue_innit();
	int size = g->links->size;//number of nodes (-1), because are counted from zero
	int i;//pomocnicza zmienna do wielu zadan
	
	//parent - an array with all the parents of all the nodes, so if parent[0] = 3 that means that node 3 is before node 0 in the path from a to b; 
	int parent[size+1];
	parent[a]=-1;
	for (i=0;i<size+1;i++)
		parent[i]=-1;
		
		
	int colour[size+1];
	for (i=0;i<size+1;i++)
		colour[i]=white; // 0 - white - not visited, 1 - black - visited or waiting
		
	Queue_push(a,q);
	colour[a]=black;
	
	
	//all the commented out printfs are just to track the code, i left it there for potential future debugging
	int current_node;
	int done=0;//like a bool to tell me if we have found the path already or not
	while(Queue_isempty(q)==0&&done==0)
	{
		//printf("starting loop!\n");
		
		current_node = Queue_pop(q);
		//printf("current node: %d\n",current_node);
		Slot ptr = Matrix_get_Slot(current_node,0,g->links);
		for (i=0;i<size+1;i++)
		{
			if(ptr->value==1&&i!=current_node)
			{
				if(colour[i]==white)
				{
					//printf("pushing queue: %d\n", i);
					Queue_push(i,q);
					//printf("parent node: parent[%d]=%d\n",i,current_node);
					parent[i]=current_node;
					colour[i]=black;
					if(i==b)
					{
						//printf("breaking loop!\n");
						done = 1;
					}
				}
			}
			ptr=ptr->right;
		}
	}
	
	list l = list_innit();
	i=b;
	if(parent[b]!=-1)	
		while(i!=-1)
		{
			list_push_back(i,l);
			i=parent[i];
		}
	return l;
}

void Graph_BFS_print(Graph g, int from, int to)
{
	list l = Graph_BFS(g, from, to);
	if(list_isempty(l))
		printf("There's no path from node %d to node %d\n",from, to);
	else
		list_print(l);
}

//HERES TWO FUNCTIONS USED TO SORT TOPOLOGICZNY--------------------------------------
void Graph_sort_step(Graph g, int node, list l, int n, int colour[], int* abort)
{
	if(colour[node]!=black)
	{	
		Slot ptr = Matrix_get_Slot(node, 0, g->links);
		colour[node]=grey;
		int i =0;
		while(ptr!=NULL)
		{
			if(ptr->value==1)
			{
				if(colour[i]==white)
					Graph_sort_step(g,i,l,g->links->size+1,colour, abort);
				if(colour[i]==grey)
					{
						*abort=1;
						break;
					}
			}
			i++;
			ptr=ptr->right;
			
		}
		
		list_push_back(node,l);
		colour[node]=black;
	}	
}

list Graph_sort_DFS(Graph g)
{
	
	int i;
	int size = g->links->size;
	int abort=0;
	
	int colour[size+1];
	for (i=0;i<size+1;i++)
		colour[i]=0; // 0 - not visited, 1 - visited or waiting
		
	list l=list_innit();

	for(i=0;i<size+1;i++)
	{
		if(abort==1)
			break;
		Graph_sort_step(g,i,l,g->links->size+1,colour,&abort);
	}
	
	if(abort==0)	
		return l;
	else
		return list_innit();
}

void Graph_sort_DFS_print(Graph g)
{
		list l = Graph_sort_DFS(g);
		if(list_isempty(l))
			printf("cannot sort, graph cyclic\n");
		else
			list_print(l);
}
//KONIEC FUNKCJI DO SORTU TOPOLOGICZNEGO--------------------------------


Graph Graph_load_from_file(FILE* fp)
{
	char c=fgetc(fp);
	int n=0;
	while(c!=EOF&&c!='\n')
	{
		if(c=='1'||c=='0')
			n++;
		c=fgetc(fp);
	}
	
	Graph g = Graph_innit(n-1);
	int i =0;
	int j =0;
	
	rewind(fp);
	c=fgetc(fp);
	while(c!=EOF )
	{
		if(c=='0')
			i++;
		else if(c=='1')
		{
			Graph_addlink(j,i,g);
			i++;
		}
		else if(c=='\n')
		{
			j++;
			i=0;
		}
			
		c = fgetc(fp);
	}
	
	return g;
}



