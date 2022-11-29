#include <stdio.h>
#include <stdlib.h>
#include "printfunctions.h"



void print_reports(long int nb_rows, int nb_columns, long int data[nb_rows][nb_columns]){
	printf("******New reports*******\n");
	for(int i = 0; i < nb_rows; i++){      
		for(int j = 0; j < nb_columns; j++){
			printf("%ld ", data[i][j]);
		}
		printf("\n");
	}
}



void print_output(int size, int output[size]){
	for(int i = 0; i<size; i++){
		printf("%d ", output[i]);
	}
	printf("\n");
}

