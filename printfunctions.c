#include <stdio.h>
#include <stdlib.h>


void copy_line(int src_idx, int dest_idx, int nb_columns, long int source[][nb_columns], long int dest[][nb_columns]){
	//printf("Copy line %d %d\n",src_idx, dest_idx);
	for(int i=0; i<nb_columns; i++){
		//printf("%d\n", source[src_idx][i]);
		dest[dest_idx][i] = source[src_idx][i];
	}
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int nb_columns, long int data[][nb_columns], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    long int L[n1][nb_columns], R[n2][nb_columns];
    
 
	    
    for (i = 0; i < n1; i++)
	    copy_line(l+i, i, nb_columns, data, L);
    for (j = 0; j < n2; j++)
	    copy_line(j+m+1, j, nb_columns, data, R);
    //printf("New step L = \n");
    //print_reports(n1,nb_columns, L);
    //printf("R = \n");
    //print_reports(n2,nb_columns, R);
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i][0] <= R[j][0]) {
	    copy_line(i,k, nb_columns, L, data);
            i++;
        }
        else {
	    copy_line(j,k, nb_columns, R, data);
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
	copy_line(i,k,nb_columns, L,data);
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
	copy_line(j,k,nb_columns, R,data);
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int nb_columns, long int data[][nb_columns], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(nb
void switch_lines(int x, int y, long int nb_lines, int nb_columns, long int data[nb_lines][nb_columns]){
	long int temp;
	if((x < nb_lines) && (y < nb_lines) && (x!=y)){
		//printf("Switch lines %d %d nb_colums %d\n", x,y,nb_columns);
		for(int i=0; i<nb_columns; i++){
			temp = data[x][i];
			data[x][i] = data[y][i];
			data[y][i] = temp;	
		}
	}

}


void quicksort(long int nb_rows, int nb_columns,long int data[nb_rows][nb_columns] ,int first,int last){
   int i, j, pivot;
   //printf("Quicksort %d %d\n", first, last);

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while((data[i][0]<=data[pivot][0]) && (i<last)){
		//printf("%d %d\n", data[i][0], data[pivot][0]);
		//printf("first while\n");
            	i++;
	 }
         while(data[j][0]>data[pivot][0]){
	    //printf("second while\n");
            j--;
	    }

         if(i<j){
            switch_lines(i,j,nb_rows,nb_columns, data);
         }
      }
      switch_lines(pivot,j,nb_rows,nb_columns, data);
      quicksort(nb_rows, nb_columns, data,first,j-1);
      quicksort(nb_rows, nb_columns, data,j+1,last);
   }
}

enum matrix_column{
	match_key = 0,
	is_trigger = 1,
	value = 2,
	breakdown_key = 3,
};

void print_reports(long int nb_rows, int nb_columns, long int data[nb_rows][nb_columns]){
	printf("******New reports*******\n");
	for(int i = 0; i < nb_rows; i++){      
		for(int j = 0; j < nb_columns; j++){
			printf("%ld ", data[i][j]);
		}
		printf("\n");
	}
}

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


void print_output(int size, int output[size]){
	for(int i = 0; i<size; i++){
		printf("%d ", output[i]);
	}
	printf("\n");
}


int main(void) {
	//Add timer !!
    FILE *fptr;
    if (!(fptr = fopen("input.txt","r"))){
              printf("Error! opening file");
              exit(1);
        }
  
    long int nb_rows;
    fscanf(fptr, "%ld", &nb_rows);
    int nb_columns = 4; 
    int nb_campaigns = 4;
    long int data[nb_rows][nb_columns];

    for(int i = 0; i < nb_rows; i++){
	    for(int j = 0; j < nb_columns; j++){
	    	fscanf(fptr, "%ld", &data[i][j]);
	   	//printf("%ld\n", data[i][j]);
	    }
        }

    fclose(fptr);
    print_reports(nb_rows, nb_columns, data);    	
    mergeSort(nb_columns, data, 0, nb_rows-1);   
    print_reports(nb_rows, nb_columns, data); 
	
    //int *  output = calloc(nb_campaigns, sizeof(int));
    int output[nb_campaigns];
    attribution(nb_rows, nb_columns, data, nb_campaigns, output);

    print_output(nb_campaigns, output);
    
    return 0;
}



