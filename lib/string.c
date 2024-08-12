
#include "lib/string.h"

char *strcpy(char *dest, const char *src)
{
    char *ptr = dest;
    while (true)
    {
        *ptr++ = *src;
        if (*src++ == EOS)
            return dest;
    }
}

char *strcat(char *dest, const char *src)
{
    char *ptr = dest;
    while (*ptr != EOS)
    {
        ptr++;
    }
    while (true)
    {
        *ptr++ = *src;
        if (*src++ == EOS)
        {
            return dest;
        }
    }
}

size_t strlen(const char *str)
{
    char *ptr = (char *)str;
    while (*ptr != EOS)
    {
        ptr++;
    }
    return ptr - str;
}

int strcmp(const char *lhs, const char *rhs)
{
    while (*lhs == *rhs && *lhs != EOS && *rhs != EOS)
    {
        lhs++;
        rhs++;
    }
    return *lhs < *rhs ? -1 : *lhs > *rhs;
}

char *strchr(const char *str, int ch)
{
    char *ptr = (char *)str;
    while (true)
    {
        if (*ptr == ch)
        {
            return ptr;
        }
        if (*ptr++ == EOS)
        {
            return NULL;
        }
    }
}

char *strrchr(const char *str, int ch)
{
    char *last = NULL;
    char *ptr = (char *)str;
    while (true)
    {
        if (*ptr == ch)
        {
            last = ptr;
        }
        if (*ptr++ == EOS)
        {
            return last;
        }
    }
}

int memcmp(const void *lhs, const void *rhs, size_t count)
{
    char *lptr = (char *)lhs;
    char *rptr = (char *)rhs;
    while (*lptr == *rptr && count-- > 0)
    {
        lptr++;
        rptr++;
    }
    return *lptr < *rptr ? -1 : *lptr > *rptr;
}

void *memset(void *dest, int ch, size_t count)
{
    char *ptr = dest;
    while (count--)
    {
        *ptr++ = ch;
    }
    return dest;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    char *ptr = dest;
    while (count--)
    {
        *ptr++ = *((char *)(src++));
    }
    return dest;
}

void *memchr(const void *str, int ch, size_t count)
{
    char *ptr = (char *)str;
    while (count--)
    {
        if (*ptr == ch)
        {
            return (void *)ptr;
        }
        ptr++;
    }
    return ptr;
}

char *strtok(char *str, const char *delim) {
    static char *next_token = NULL; // 保存上次的剩余字符串
    if (str != NULL) {
        next_token = str; // 如果传入的字符串不为空，则处理该字符串
    }
    if (next_token == NULL) {
        return NULL; // 如果没有更多的字符串，则返回NULL
    }

    // 跳过前导的分隔符
    while (*next_token && strchr(delim, *next_token)) {
        next_token++;
    }

    if (*next_token == '\0') {
        return NULL; // 如果已经到达字符串末尾，则返回NULL
    }

    char *start = next_token;

    // 找到下一个分隔符
    while (*next_token && !strchr(delim, *next_token)) {
        next_token++;
    }

    if (*next_token) {
        *next_token = '\0'; // 用'\0'替换分隔符，将标记分割开
        next_token++; // 准备处理下一个标记
    } else {
        next_token = NULL; // 如果已到达字符串末尾，则设置为NULL
    }

    return start;
}