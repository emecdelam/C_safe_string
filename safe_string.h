#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_MALLOC_FAIL (void *) -1
#define STRING_OVERFLOW -1
#define STRING_SUCCESS 0
#define STRING_INVALID_INPUT 1
typedef struct {
    char *buffer;
    size_t max_length;
} safe_string;


