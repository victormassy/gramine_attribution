#include <stdio.h>
#include <stdlib.h>
#include "matrix_columns.h"


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



