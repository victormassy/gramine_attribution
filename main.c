#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_columns.h"
#include "mergesort.h"
#include "quicksort.h"
#include "printfunctions.h"
#include "insertionsort.h"
#include "grouping.h"

void attribution(int nb_rows, int nb_columns, long int data[nb_rows][nb_columns], int nb_campaigns, int output[nb_campaigns]){
	//Naive implementation 
	//For now, we assume that the input list is sorted by timestamps 
	//merge sort and quicksort are stable so in the sorted matrix,
	//for a define matchkey, timestamps are sorted
	for(int i = 0; i<nb_campaigns; i++){
		output[i] = 0;
	} 
	int j;
	enum matrix_column key = match_key;
	enum matrix_column trigger = is_trigger; 
	enum matrix_column val = value; 
	enum matrix_column breakdown = breakdown_key;
	//if first element is trigger can't attritube it to any source
	for(int i = 1; i < nb_rows; i++){
		//for each trigger event find the closer source event 
		if(data[i][trigger]){
			j = i - 1;		
			//looping on the same match key 
			
			while(data[j][key] == data[i][key] && j > 0){
				//When the closer (in time) source event is found, add trigger value to source campaign
				
				if(!data[j][trigger]){
					output[data[j][breakdown]] += data[i][val];	
					break; 
				}
				else 
					j -= 1;
			
			}	
		}

	}

}


int main(void) {
    clock_t start = clock();
    FILE *fptr;
    if (!(fptr = fopen("input.txt","r"))){
              printf("Error! opening file");
              exit(1);
        }
  
    long int nb_rows;
    if(!fscanf(fptr, "%ld", &nb_rows)) exit(2);
    int nb_columns = 4; 
    int nb_campaigns = 100;
    long int data[nb_rows][nb_columns];
    int output[nb_campaigns];

    for(int i = 0; i < nb_rows; i++){
	    for(int j = 0; j < nb_columns; j++){
	    	if(!fscanf(fptr, "%ld", &data[i][j])) exit(3);
	   	//printf("%ld\n", data[i][j]);
	    }
        }

    fclose(fptr);
    print_reports(nb_rows, nb_columns, data);    	
    
    /*
     * First solution: merge sort 
     */

//    mergeSort(nb_columns, data, 0, nb_rows-1);   
//    attribution(nb_rows, nb_columns, data, nb_campaigns, output);
//    print_output(nb_campaigns, output);
    
    //quicksort(nb_rows, nb_columns, data, 0, nb_rows-1);
	
    /*
     * Second solution: insertion sort
     */
    insertion_sort(nb_rows, nb_columns, data);
    attribution(nb_rows, nb_columns, data, nb_campaigns, output);
    print_output(nb_campaigns, output);
    
    /*
     * Third solution: homemade algorithm 
     */ 
//    group_rows_by_keys(nb_rows, nb_columns, nb_campaigns, data);
    
    
    clock_t stop = clock();
    
    clock_t difference = stop - start;
    int msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds \n", msec/1000, msec%1000);
    return 0;
}


