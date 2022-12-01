#ifndef GROUPING
#define GROUPING

#include<stdbool.h>


struct element
{
	long int * row;
	struct element * next_element; 
};


struct tree
{
	long int key; 
	struct element * element; 
	bool contains_trigger;
       	int nb_elements;	
	struct tree * next;
};



void group_rows_by_keys(int nb_rows, int nb_columns, int nb_campaings, long int data[nb_rows][nb_columns]);


#endif 
