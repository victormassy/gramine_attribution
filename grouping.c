#include "grouping.h"
#include <stdio.h>
#include<stdbool.h>

bool is_part(struct tree * tree, long int key, struct tree * found)
{
	found = tree;
	while(tree->next != NULL)
	{
		if(tree->key == key){
			found = tree;
			return true;
		}
		tree = tree -> next;
	}
	return false; 
}

bool add_key(struct tree * tree, long int key, struct tree * found_key)
{
	//If found return false and store position 
	if(is_part(&tree, key, found_key)) return false;
	//If not found allocate a new node in the tree  
	struct tree * head = calloc(1,sizeof(struct tree));
	head -> key = key;
	head -> nb_elements = 1;  
	head -> next = &tree; 
	tree = head; 
	found_key = tree; 
	return true; 
}


void print_tree(struct tree * to_print){
	while(to_print->next != NULL){
		printf("%ld\n", to_print->key);
		to_print = to_print->next;
	}
}


void group_rows_by_keys(int nb_rows, int nb_columns, long int data[nb_rows][nb_columns])
{
	int i,j;
	struct tree * known_keys;
	bool added;
	struct tree * found_key; 
	long int grouped_data[nb_rows][nb_columns]; 
	for(i=0;i<nb_rows;i++)
	{
		added = add_key(known_keys, data[i][0], found_key);
		struct element * new_element = malloc(1, sizeof(struct element)) ;
		new_element->row = data[i];
		new_element->next_element = found_key->next; 
		found_key -> next = new_element;
	}

}
