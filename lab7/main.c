#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void strcopy(char *dst, char *src, size_t len);

int64_t getstrlen(const char *string)
{
    int64_t res;
    asm ("mov %1, %%rdi\n\t"
         "mov $-1, %%rcx\n\t"
         "mov $0, %%al\n\t"
         "repne scasb\n\t"
         "not %%rcx\n\t"
         "dec %%rcx\n\t"
         "mov %%rcx, %0"
         : "=r" (res)
         : "r" (string)
         : "rdi", "rcx", "rax");
    return res;
}

int main(void)
{
    const char *string = "1234";
    int64_t res = getstrlen(string);
    printf("%" PRId64 "\n", res);
    char src[] = "abcd";
    char dst[] = "zyxw";
    size_t len = 2;
    strcopy(dst, src, len);
    printf("%s\n", dst);
    return 0;
}
