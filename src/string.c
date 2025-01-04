#include "../include/string.h"
typedef unsigned int size_t;  // Or another appropriate type

int strlen(const char *str) {
    int length = 0;
    while (*str++) {
        length++;
    }
    return length;
}

char *custom_strcpy(char *dest, const char *src) {
    char *original = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return original;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

char *strncpy(char *dest, const char *src, size_t n) {
    char *original = dest;
    while (n && (*dest++ = *src++)) {
        n--;
    }
    if (n) {
        while (--n) {
            *dest++ = '\0';
        }
    }
    return original;
}

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}
// Function to compare the first n characters of two strings
// Implement strncmp to compare the first n characters of two strings
int strncmp(const char *str1, const char *str2, size_t n) {
    while (n--) {
        if (*str1 != *str2) {
            return (unsigned char)*str1 - (unsigned char)*str2;
        }
        if (*str1 == '\0') {
            return 0;  // Strings are equal up to the null terminator
        }
        str1++;
        str2++;
    }
    return 0;  // If we reach here, the first n characters are equal
}



void *memset(void *ptr, int value, size_t num) {
    unsigned char *p = (unsigned char *)ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}
