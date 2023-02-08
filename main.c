#include "grouping.h"
#include "insertionsort.h"
#include "matrix_columns.h"
#include "mergesort.h"
#include "printfunctions.h"
#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void attribution(int nb_rows, int nb_columns,
                 long int data[nb_rows][nb_columns], int nb_campaigns,
                 int output[nb_campaigns]) {
  // Naive implementation
  // We assume that the input list is sorted by timestamps
  // merge sort and quicksort are stable so in the sorted matrix,
  // for a define matchkey, timestamps are sorted
  for (int i = 0; i < nb_campaigns; i++) {
    output[i] = 0;
  }
  int j;
  enum matrix_column key = match_key;
  enum matrix_column trigger = is_trigger;
  enum matrix_column val = value;
  enum matrix_column breakdown = breakdown_key;
  // if first element is trigger can't attritube it to any source
  // loop starts at index 1
  for (int i = 1; i < nb_rows; i++) {
    // for each trigger event find the closest source event
    if (data[i][trigger]) {
      j = i - 1;
      // looping backward while match key is the same
      while (data[j][key] == data[i][key] && j >= 0) {
        // When the closer (in time) source event is found,
        // add trigger value to source campaign
        if (!data[j][trigger]) {
          output[data[j][breakdown]] += data[i][val];
          break;
        } else
          j -= 1;
      }
    }
  }
}

int main(void) {
  pid_t pid = getpid();
  FILE *fmem;
  char *buf;
  asprintf(&buf, "proc/%d/status", pid);
  if (!(fmem = fopen(buf, "r"))) {
    exit(1);
  }

  clock_t start = clock();
  FILE *fptr;
  if (!(fptr = fopen("input.txt", "r"))) {
    printf("Error! opening input");
    exit(1);
  }

  long int nb_rows;
  //Number of rows should be at line 1
  if (!fscanf(fptr, "%ld", &nb_rows))
    exit(2);
  
  int nb_columns = 4;
  int nb_campaigns = 100;
  long int data[nb_rows][nb_columns];
  int output[nb_campaigns];
  //Fill matrix with input data
  for (int i = 0; i < nb_rows; i++) {
    for (int j = 0; j < nb_columns; j++) {
      if (!fscanf(fptr, "%ld", &data[i][j])) {
        printf("Error in file");
        exit(3);
      }
    }
  }

  fclose(fptr);
  /*
   * First solution: merge sort
   */

  mergeSort(nb_columns, data, 0, nb_rows - 1);
  attribution(nb_rows, nb_columns, data, nb_campaigns, output);
  //For test purpose you can comment the following line
  print_output(nb_campaigns, output);

  /*
   * Second solution: insertion sort
   */
   //  insertion_sort(nb_rows, nb_columns, data);
   // attribution(nb_rows, nb_columns, data, nb_campaigns, output);
  //   print_output(nb_campaigns, output);

  /*
   * Third solution: homemade algorithm
   */
  //    group_rows_by_keys(nb_rows, nb_columns, nb_campaigns, data);

  clock_t stop = clock();

  clock_t difference = stop - start;
  int microsec = difference * 1000000 / CLOCKS_PER_SEC;
  printf("%d \n", microsec);
  return 0;
}
