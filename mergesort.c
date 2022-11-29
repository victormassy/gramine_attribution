#include <stdio.h>
#include <stdlib.h>
#include "matrix_columns.h"

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
        mergeSort(nb_columns, data, l, m);
        mergeSort(nb_columns, data, m + 1, r);
 
        merge(nb_columns, data, l, m, r);
    }
}
