#include "insertionsort.h"
#include "mergesort.h"
#include <math.h>
#include <stdio.h>

// Insertion Sort Function
void insertion_sort(int nb_columns, int nb_rows,
                    long int data[nb_rows][nb_columns]) {
  int i, element, j;
  int curr_key;
  for (i = 1; i < nb_rows; i++) {
    curr_key = data[i][0];
    j = i - 1;
    while (j >= 0 && data[j][0] > curr_key) {
      copy_line(j, j + 1, nb_columns, data, data);
      j = j - 1;
    }
    copy_line(i, j + 1, nb_columns, data, data);
  }
}
