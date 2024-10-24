/**
 * Copyright 2024 Jim Haslett
 *
 * This work part of a university assignment.  If you are taking the course
 * this work was assigned for, do the right thing, and solve the assignment
 * yourself!
 *
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/* Define constants */
#define MATRIX_SIZE 2048
#define OUTFILENAME "result.txt"
#define TIMEFILENAME "times.tsv"

/* Forward declare thread function */
void *compute_rows(void *);

/* Declare matricies */
int matrix_a_[MATRIX_SIZE * MATRIX_SIZE];
int matrix_b_[MATRIX_SIZE * MATRIX_SIZE];
int matrix_c_[MATRIX_SIZE * MATRIX_SIZE];

void main() {
    /**
     * main function
     *
     * This is the main function that does all the work
     */

    printf("OMP_NUM_THREADS : %s\n", getenv("OMP_NUM_THREADS"));
    printf("OMP_SCHEDULE : %s\n", getenv("OMP_SCHEDULE"));

    /* File Pointer for output */
    FILE *outfile, *timefile;

    /* Timing varilables */
    double begin, end;

    /* Loop index variables */
    // int i, j, k;

    /* Fill matricies */
    int val;
    for (int i=0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
        matrix_a_[i] = 1;
        matrix_b_[i] = 2;
        matrix_c_[i] = 0;
    }

    begin = omp_get_wtime();
    
    /* Loops to compute matrix multiplcation */
    #pragma omp parallel for shared (matrix_a_, matrix_b_, matrix_c_)
    for (int i = 0; i < MATRIX_SIZE; i++) {  // row
        for (int j = 0; j < MATRIX_SIZE; j++) { // column
            for (int k = 0; k < MATRIX_SIZE; k++) { // cell in row/column
                matrix_c_[i*MATRIX_SIZE + j] += matrix_a_[i*MATRIX_SIZE + k] * matrix_b_[k*MATRIX_SIZE + j];
            }
        }
    }

    end = omp_get_wtime();

    /* Output result matrix to file */
    outfile = fopen(OUTFILENAME, "w");
    for (int j=0; j < MATRIX_SIZE; j++) {
        for (int i=0; i < MATRIX_SIZE; i++) {
            fprintf(outfile, "%4d ", matrix_c_[j*MATRIX_SIZE + i]);
        }
        fprintf(outfile, "\n");
    }
    fclose(outfile);

    timefile = fopen(TIMEFILENAME, "a");
    fprintf(timefile, "%s\t %s\t %.8f\n", getenv("OMP_SCHEDULE"), getenv("OMP_NUM_THREADS"),(end-begin));
    fclose(timefile);


    printf("Execution Time: %.8f\n", (end-begin));
}

