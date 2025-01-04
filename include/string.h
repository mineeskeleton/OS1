#ifndef STRING_H
#define STRING_H

typedef unsigned int size_t;  // Or another appropriate type

int strlen(const char *str);
char *custom_strcpy(char *dest, const char *src);
int strcmp(const char *str1, const char *str2); 
char *strncpy(char *dest, const char *src, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *ptr, int value, size_t num);
int strncmp(const char *str1, const char *str2, size_t n);


#endif // STRING_H