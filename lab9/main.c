#include <stdio.h>
#include "my_matrix.h"


int main(void)
{
    size_t m1, n1, m2, n2;
    matrix_t matr1 = {0}, matr2 = {0};
    printf("Введите размеры матрицы 1:\n");
    scanf("%zu %zu", &n1, &m1);
    printf("Введите матрицу 1:\n");
    input_matrix(n1, m1, matr1);
    printf("Введите размеры матрицы 2:\n");
    scanf("%zu %zu", &n2, &m2);
    printf("Введите матрицу 2:\n");
    input_matrix(n2, m2, matr2);
    transpose(n2, m2, matr2);
    matrix_t res = {0};
    for (size_t i = 0; i < n1; ++i)
        for (size_t j = 0; j < m2; ++i)
        {
            double tmp = 0, read = 0;
            for (size_t k = 0; k < m1; k += 2 * sizeof(double))
            {
                size_t step1 = k + i * MAX_N * sizeof(double);
                size_t step2 = k + j * MAX_N * sizeof(double);
                asm(
                    "movupd (%1), %%xmm0\n"
                    "movupd (%2), %%xmm1\n"
                    "mulpd %%xmm1, %%xmm0\n"
                    "haddpd %%xmm0, %%xmm0\n"
                    "movsd %%xmm0, %0\n"
                    : "=m" (tmp)
                    : "r" (matr1 + step1), "r" (matr2 + step2)
                );
                read += tmp;
            }
            res[i * m1 + j] = read;
        }
    output_matrix(m1, n2, res);
}