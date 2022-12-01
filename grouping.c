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

void print_element(struct element * elem){
		printf("elem : key %ld, is trigger: %d, value %ld", elem->row[0], elem->row[1], elem->row[2]);
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

void grouped_attribution(long int * output, struct tree * tree, int nb_campaigns){
	
	enum matrix_column trigger = is_trigger; 
	enum matrix_column key = match_key;
	enum matrix_column val = value; 
	enum matrix_column breakdown = breakdown_key;
    	struct element * curr;
    	struct element * linked_source;
	//Check all the different match keys
	while(tree != NULL){		
		printf("new key\n");
		//If a key contains at least one trigger, check all the elements
		if(tree->contains_trigger && tree->nb_elements>1){
			curr = tree->element;
			while(curr != NULL){
				//we want to find the matching source
				printf("%d\n", curr->row[1]);
				if(curr->row[trigger]){
					printf("found trigger\n");
					linked_source = curr ->next_element;
					//go through all previous elem and find the closer source event 
					while(linked_source != NULL){
						if(!linked_source->row[trigger]){
							printf("found source\n");
							output[linked_source->row[breakdown]] += curr->row[2]; 
							print_element(linked_source);
							break; 
						}
						linked_source = linked_source -> next_element; 
					}
				}
            			curr = curr ->next_element;
        		}
		}
        	tree = tree -> next;
	}
	
}



void group_rows_by_keys(int nb_rows, int nb_columns, int nb_campaigns, long int data[nb_rows][nb_columns])
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

	long int output[nb_campaigns]; 
	
	for(int i = 0; i<nb_campaigns; i++){
	              output[i] = 0; 
	}

	grouped_attribution(output, known_keys, nb_campaigns); 
 		
	for(int i = 0; i<nb_campaigns; i++){
		printf("%d ", output[i]);
	}
	
//	free(output);
	printf("\n");	
	free_tree(known_keys);
	

}

