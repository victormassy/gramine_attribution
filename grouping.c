#include "grouping.h"
#include <stdio.h>


struct element
{
	int * row;
	struct element * next_element; 
}


struct tree
{
	struct * match_key key; 
	struct element * element; 
	struct * match_key next;
}



bool is_part(struct tree tree, long int key, struct tree * found)
{
	found = tree;
	while(tree->next != NULL)
	{
		if(tree->key.value == key){
			found = tree;
			return true;
		}
		tree = tree -> next;
	}
	return false; 
}

bool add_key(struct tree * tree, long int key, int * idx)
{
	if(is_part(&tree, key, idx)) return false; 
	struct tree * head = calloc(1,sizeof(struct tree));
	head -> value = key; 
	head -> next = &tree; 
	tree = head; 
	&idx = 0;
	return true; 
}


void group_rows_by_keys(int nb_rows, int nb_columns, long int data[nb_rows][nb_columns])
{
	int i,j;
	struct tree * known_keys;
	bool added;
	int * idx; 
	long int grouped_data[nb_rows][nb_columns]; 
	for(i=0;i<nb_rows;i++)
	{
		added = add_key(known_keys, key, idx);
		if(added)
		{
			struct element * new_element = malloc(1, sizeof(struct element)) ;
			tree -> element = new_element; 
		}

	}
}
