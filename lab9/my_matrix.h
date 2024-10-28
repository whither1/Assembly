#ifndef MY_MATRIX_H

#define MY_MATRIX_H

#include <stdio.h>

#define MAX_N 12
#define MAX_M 12
#define MTX_SIZE MAX_N * MAX_M

typedef double matrix_t[MTX_SIZE];

#define ERR_MEMORY 11
#define ERR_SIZE 12
#define ERR_INPUT 13
#define ERR_RANGE 14
#define ERR_DET 15
#define SUCCESS 0

int input_matrix(size_t rows, size_t cols, matrix_t matr);
void output_matrix(size_t rows, size_t cols, matrix_t matr);
void transpose(size_t rows, size_t cols, matrix_t matr);

#endif