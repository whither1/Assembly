#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include "my_matrix.h"

int input_matrix(size_t rows, size_t cols, matrix_t matr)
{   
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
    {
        if (scanf("%lf", &(matr[i * cols + j])) != 1)
        {
            return ERR_INPUT;
        }
    }
    return SUCCESS;
}

void output_matrix(size_t rows, size_t cols, matrix_t matr)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
            printf("%.6lf ", matr[i * cols + j]);
        printf("\n");
    }
}

void transpose(size_t rows, size_t cols, matrix_t matr)
{
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = i; j < cols; ++j)
        {
            double tmp = matr[i * cols + j];
            matr[j * cols + i] = tmp;
            matr[i * cols + j] = matr[j * cols + i];
        }
}
