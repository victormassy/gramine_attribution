#ifndef GROUPING
#define GROUPING

#include<stdbool.h>


struct element
{
	int * row;
	struct element * next_element; 
};


struct tree
{
	long int key; 
	struct element * element; 
	int nb_elements; 
	struct tree * next;
};



bool is_part(struct tree * tree, long int key, struct tree * found);
bool add_key(struct tree * tree, long int key, struct tree * found_key);
void group_rows_by_keys(int nb_rows, int nb_columns, long int data[nb_rows][nb_columns]);


#endif 