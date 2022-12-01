#include "grouping.h"
#include "matrix_columns.h"
#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>


bool is_part(struct tree * tree, long int key, struct tree ** found)
{
	*found = tree;
	while(tree != NULL)
	{	
		if(tree->key == key){
			*found = tree;
			return true;
		}
		tree = tree -> next;
	}	
	return false; 
}

struct tree * add_key(struct tree * tree, long int key, struct tree ** found_key)
{
	if(!is_part(tree, key, found_key)){
		//If not found allocate a new node in the tree  
 		printf("add key\n");	
		struct tree * head = malloc(sizeof(struct tree));
		head -> key = key;
		head -> nb_elements = 1;  
		head -> next = tree;
	        head -> nb_elements = 0;
		head -> contains_trigger = false;	
		//printf("tree before : %d\n", tree);
		tree = head; 
		//printf("tree after : %d\n", tree);
	} 
	return tree;
}

void free_tree(struct tree * tree){
        struct tree * next_node;
        struct element * elem;
        struct element * next_elem;
        while(tree->next != NULL){
                next_node = tree ->next;
                elem = tree->element;
                while(elem != NULL){
                        next_elem = elem -> next_element;
                        free(elem);
                        elem = next_elem;
                }
                free(tree);
                tree = next_node;
        }
}
void print_tree(struct tree * to_print){
	printf("Print tree\n");
	struct element * curr; 
	while(to_print != NULL){
		printf("key: %ld nb elements: %d contains trigger: %d-> elements: ", to_print->key, to_print->nb_elements, to_print->contains_trigger);
		curr = to_print->element;	
		while(curr != NULL){
			printf("%ld %ld %ld ", curr->row[1], curr->row[2], curr->row[3]);
			curr = curr->next_element;
		}
		printf("\n");
		to_print = to_print->next;

	}
}

struct tree * init_tree(int nb_rows, int nb_columns, long int data[nb_rows][nb_columns]){
	struct tree * tree = malloc(sizeof(struct tree));
        tree -> key = data[0][0];
	tree -> next = NULL;
	tree -> contains_trigger = false; // if first line is a trigger it is impossible to match 
	tree -> nb_elements = 1; 
	struct element * element = malloc(sizeof(struct element));
	tree -> element = element;	
	element -> row = data[0];
	element -> next_element = NULL;
	return tree; 
}


void group_rows_by_keys(int nb_rows, int nb_columns, long int data[nb_rows][nb_columns])
{
	int i,j;
	struct tree * known_keys = init_tree(nb_rows, nb_columns, data);
	bool added;
	struct tree ** found_key = &known_keys;	
	struct element * new_element; 
       	enum matrix_column is_trigger = is_trigger; 
	enum matrix_column match_key = match_key;	
	for(i=1;i<nb_rows;i++)
	{	
		known_keys = add_key(known_keys, data[i][match_key], found_key);		
		new_element = malloc(sizeof(struct element)) ;
		new_element->row = data[i];
		new_element->next_element = (*found_key)->element; 
		(*found_key) -> element = new_element;
		(*found_key) -> nb_elements +=1; 
		if(new_element->row[is_trigger]) (*found_key)->contains_trigger = true;
	
	}
	print_tree(known_keys);
	free_tree(known_keys);
	

}


int * aggregation(struct tree * tree){
	
}

