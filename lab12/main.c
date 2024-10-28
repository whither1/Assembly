#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define BUF_SIZE 100

size_t string_length(const char *str)
{
    size_t len = 0;
    asm(
    "1:\n"
    "ldrb w0, [%[str], %[len]]\n"
    "add %[len], %[len], #1\n"
    "cmp w0, #0\n"
    "bne 1b\n"
    "sub %[len], %[len], #1\n"
    : [len] "+r" (len)
    : [str] "r" (str)
    : "cc", "memory", "w0"
    );
    return len;
}

void add_arrays_neon(int32_t *result, const int32_t *arr1, const int32_t *arr2, size_t length)
{
    for (size_t i = 0; i < length + 5; i += 4)
    {
        asm(
        "ld1 {v0.4s}, [%[arr1]]\n"
        "ld1 {v1.4s}, [%[arr2]]\n"
        "add v2.4s, v0.4s, v1.4s\n"
        "st1 {v2.4s}, [%[result]], #16\n"
        : [result] "+r"(result)
        : [arr1] "r"(arr1), [arr2] "r"(arr2)
        : "v0", "v1", "v2", "memory"
        );
        arr1 += 4;
        arr2 += 4;
    }
}

int scan_array(int32_t *arr, size_t alen)
{
    for (size_t i = 0; i < alen; ++i)
        if (scanf("%" SCNd32, &arr[i]) != 1)
            return 1;
    return 0;
}

int main()
{
    char str[BUF_SIZE];

    printf("Введите строку:\n");
    if (!fgets(str, BUF_SIZE, stdin))
        return 1;

    size_t length = string_length(str);
    printf("Длина строки: %zu\n", length);

    int32_t array1[BUF_SIZE];
    int32_t array2[BUF_SIZE];
    int32_t result[BUF_SIZE];
    size_t alen;

    printf("Введите длину, складываемых массивов:\n");
    if (scanf("%zu", &alen) != 1)
        return 2;

    printf("Введите первый массив:\n");
    if (scan_array(array1, alen))
        return 3;

    printf("Введите второй массив:\n");
    if (scan_array(array2, alen))
        return 4;

    add_arrays_neon(result, array1, array2, alen);

    printf("Итоговый массив:\n");
    for (int i = 0; i < alen; ++i)
        printf("%" PRId32 " ", result[i]);
    printf("\n");

    return 0;
}