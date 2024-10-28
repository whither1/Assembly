#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <math.h>

unsigned long long nanosecnow(void)
{
    struct timespec millsec;
    clock_gettime(CLOCK_REALTIME, &millsec);
    return millsec.tv_sec * 1e9 + millsec.tv_nsec;
}

float sum_float_c(void)
{
    float a = 12345, b = 67890;
    float c = a + b;
    return c;
}

float mul_float_c(void)
{
    float a = 12345, b = 67890;
    float c = a * b;
    return c;
}

double sum_double_c(void)
{
    double a = 12345, b = 67890;
    double c = a + b;
    return c;
}

double mul_double_c(void)
{
    double a = 12345, b = 67890;
    double c = a * b;
    return c;
}

void output_times_c(size_t test_am)
{
    printf("Вывод времени на C(нс):\n");
    unsigned long long time = 0;
    for (size_t i = 0; i < test_am; ++i)
    {
        unsigned long long beg = nanosecnow();
        sum_float_c();
        unsigned long long end = nanosecnow();
        time += end - beg;
    }
    double res = (double)time / test_am;
    printf("Сложение 32-разрядных чисел: %lf\n", res);

    time = 0;
    for (size_t i = 0; i < test_am; ++i)
    {
        unsigned long long beg = nanosecnow();
        mul_float_c();
        unsigned long long end = nanosecnow();
        time += end - beg;
    }
    res = (double)time / test_am;
    printf("Умножение 32-разрядных чисел: %lf\n", res);

    time = 0;
    for (size_t i = 0; i < test_am; ++i)
    {
        unsigned long long beg = nanosecnow();
        sum_double_c();
        unsigned long long end = nanosecnow();
        time += end - beg;
    }
    res = (double)time / test_am;
    printf("Сложение 64-разрядных чисел: %lf\n", res);

    time = 0;
    for (size_t i = 0; i < test_am; ++i)
    {
        unsigned long long beg = nanosecnow();
        mul_double_c();
        unsigned long long end = nanosecnow();
        time += end - beg;
    }
    res = (double)time / test_am;
    printf("Умножение 64-разрядных чисел: %lf\n", res);
}

float sum_float_asm(void)
{
    float a = 12345.0, b = 67890.0;
    float c;
    asm ("flds %1\n\t"
         "fadds %2\n\t"
         "fstps %0"
         : "=m" (c)
         : "m" (a), "m" (b));
    return c;
}

float mul_float_asm(void)
{
    float a = 12345.0, b = 67890.0;
    float c;
    asm ("flds %1\n\t"
         "fmuls %2\n\t"
         "fstps %0"
         : "=m" (c)
         : "m" (a), "m" (b));
    return c;
}

double sum_double_asm(void)
{
    double a = 12345.0, b = 67890.0;
    double c;
    asm ("fldl %1\n\t"
         "faddl %2\n\t"
         "fstpl %0"
         : "=m" (c)
         : "m" (a), "m" (b));
    return c;
}

double mul_double_asm(void)
{
    double a = 12345.0, b = 67890.0;
    double c;
    asm ("fldl %1\n\t"
         "fmull %2\n\t"
         "fstpl %0"
         : "=m" (c)
         : "m" (a), "m" (b));
    return c;
}

void output_times_asm(size_t test_am)
{
    printf("Вывод времени на ассемблере(нс):\n");
    unsigned long long time = 0;
    for (size_t i = 0; i < test_am; ++i)
    {
        unsigned long long beg = nanosecnow();
        sum_float_asm();
        unsigned long long end = nanosecnow();
        time += end - beg;
    }
    double res = (double)time / test_am;
    printf("Сложение 32-разрядных чисел: %lf\n", res);

    time = 0;
    for (size_t i = 0; i < test_am; ++i)
    {
        unsigned long long beg = nanosecnow();
        mul_float_asm();
        unsigned long long end = nanosecnow();
        time += end - beg;
    }
    res = (double)time / test_am;
    printf("Умножение 32-разрядных чисел: %lf\n", res);

    time = 0;
    for (size_t i = 0; i < test_am; ++i)
    {
        unsigned long long beg = nanosecnow();
        sum_double_asm();
        unsigned long long end = nanosecnow();
        time += end - beg;
    }
    res = (double)time / test_am;
    printf("Сложение 64-разрядных чисел: %lf\n", res);

    time = 0;
    for (size_t i = 0; i < test_am; ++i)
    {
        unsigned long long beg = nanosecnow();
        mul_double_asm();
        unsigned long long end = nanosecnow();
        time += end - beg;
    }
    res = (double)time / test_am;
    printf("Умножение 64-разрядных чисел: %lf\n", res);
}

void output_cmp_sin(void)
{
    double pi = 3.14;
    printf("Значение пи: %lf\n", pi);
    double res;
    asm("fldl %1\n\t"
        "fsin\n\t"
        "fstpl %0"
        : "=m" (res)
        : "m" (pi));
    printf("sin(π) = %lf\n", res);
    pi /= 2;
    asm("fldl %1\n\t"
        "fsin\n\t"
        "fstpl %0"
        : "=m" (res)
        : "m" (pi));
    printf("sin(π/2) = %lf\n", res);

    pi = 3.141596;
    printf("Значение пи: %lf\n", pi);
    asm("fldl %1\n\t"
        "fsin\n\t"
        "fstpl %0"
        : "=m" (res)
        : "m" (pi));
    printf("sin(π) = %lf\n", res);
    pi /= 2;
    asm("fldl %1\n\t"
        "fsin\n\t"
        "fstpl %0"
        : "=m" (res)
        : "m" (pi));
    printf("sin(π/2) = %lf\n", res);

    printf("Значение пи: загружаетсся сопроцессором\n");
    asm("fldpi\n\t"
        "fsin\n\t"
        "fstpl %0"
        : "=m" (res));
    printf("sin(π) = %lf\n", res);
    const double two = 2; 
    asm("fldpi\n\t"
        "fdivl %1\n\t"
        "fsin\n\t"
        "fstpl %0"
        : "=m" (res)
        : "m" (two));
    printf("sin(π/2) = %lf\n", res);   
}

double find_root(double a, double b, int amount)
{
    double res, eps = 1e-8, two = 2.0, tmp, seven = 7.0, zero = 0.0;
    amount++;
    asm (
        "beg:\n\t"
        "decl %7\n\t"
        "fldl %1\n\t"
        "faddl %2\n\t"
        "fdivl %4\n\t"
        "fld %%st(0)\n\t"
        "fmul %%st(1)\n\t"
        "fmul %%st(1)\n\t"
        "faddl %6\n\t"
        "fcos\n\t"
        "fld %%st(0)\n\t"
        "fabs\n\t"
        "fldl %5\n\t"
        "fcompp\n\t"
        "fstsw %%ax\n\t"
        "sahf\n\t"
        "jl ending\n\t"
        "mov %7, %%cx\n\t"
        "cmpw %%cx, %8\n\t"
        "je ending\n\t"
        "fldl %1\n\t"
        "fstl %3\n\t"
        "fmull %3\n\t"
        "fmull %3\n\t"
        "faddl %6\n\t"
        "fcos\n\t"
        "fmulp\n\t"
        "ftst\n\t"
        "fstsw %%ax\n\t"
        "sahf\n\t"
        "ja change_first\n\t"
        "fstpl %3\n\t"
        "fstpl %2\n\t"
        "jmp beg\n\t"
        "change_first:\n\t"
        "fstpl %3\n\t"
        "fstpl %1\n\t"
        "jmp beg\n\t"
        "ending:\n\t"
        "fstpl %3\n\t"
        "fstpl %0\n\t"
        : "=m" (res), "=m" (a), "=m"(b), "=m" (tmp)
        : "m" (two), "m" (eps), "m" (seven), "m" (amount), "m" (zero)
        : "ax", "cx"
    );
    return res;
}

// double func(double x)
// {
//     double res, seven = 7.0;
//     asm (
//         "fldl %1\n\t"
//         "fmull %1\n\t"
//         "fmull %1\n\t"
//         "faddl %2\n\t"
//         "fcos\n\t"
//         "fstpl %0"
//         : "=m" (res)
//         : "m" (x), "m" (seven)
//     );
//     return res;
// }

// double find_mid(double a, double b)
// {
//     double res, two = 2.0;
//     asm (
//         "fldl %1\n\t"
//         "faddl %2\n\t"
//         "fdivl %3\n\t"
//         "fstpl %0"
//         : "=m" (res)
//         : "m" (a), "m" (b), "m" (two)
//     );
//     return res;
// }

// double find_root(double a, double b, int amount)
// {
//     double eps = 1e-8;
//     double mid, f_mid;
//     for (int i = 0; i < amount; i++) {
//         mid = find_mid(a, b);
//         f_mid = func(mid);
//         if (fabs(f_mid) < eps) {
//             return mid;
//         }
//         double f_a = func(a);
//         if (f_mid * f_a < 0) {
//             b = mid;
//         }
//         else {
//             a = mid;
//         }
//     }
//     return mid;
// }

void check(void)
{
    double res1 = 3, res2 = 12, a = 5, b = 10, c = 6;
    asm (
        "fldl %2\n\t"
        "fld %%st(0)\n\t"
        "faddl %3\n\t"
        "fstpl %0\n\t"
        "fstpl %1\n\t"
        : "=m" (res1), "=m" (res2)
        : "m" (a), "m" (b), "m" (c)
    );
    printf("%lf\n%lf", res1, res2);
}
int main(void)
{
    size_t test_am = 1e6;
    output_times_c(test_am);
    output_times_asm(test_am);
    output_cmp_sin();
    double a, b;
    int amount;
    printf("Введите левую и правую границы отрезка: ");
    scanf("%lf %lf", &a, &b);
    printf("Введите кол-во итераций: ");
    scanf("%d", &amount);
    double res = find_root(a, b, amount);
    printf("Корень функции cos(x^3 + 7) методом половинного деления: %lf\n", res);
    // check();
    return 0;
}
