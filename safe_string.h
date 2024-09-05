#ifndef SAFE_STRING_H
#define SAFE_STRING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_MALLOC_FAIL (void *) -1
#define STRING_OVERFLOW -1
#define STRING_SUCCESS 0
#define STRING_INVALID_INPUT -2


typedef struct {
    char *buffer;
    size_t max_length;
} safe_string;

void *custom_calloc(size_t size);
safe_string *create_string(size_t max_length);
size_t get_string_size(safe_string *s);
int set_string(safe_string *s, const char *str);
int append_string(safe_string *s, const char *str);
void print_string(const safe_string *str, FILE *stream);
safe_string *initialize_safe_string(const char * str);
void destroy_string(safe_string *s);

#endif