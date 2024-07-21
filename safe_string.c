#include "safe_string.h"

void *custom_calloc(size_t size) {
    if (size == 0) {
        return STRING_MALLOC_FAIL;
    }
    void *p = malloc(size);
    if (p == NULL) {
        return STRING_MALLOC_FAIL;
    }
    memset(p, 0, size);
    return p;
}
safe_string *create_string(size_t max_length) {
    safe_string *s = custom_calloc(sizeof(safe_string));
    if (s == STRING_MALLOC_FAIL){
        return STRING_MALLOC_FAIL;
    }
    s->buffer = custom_calloc(max_length * sizeof(char));
    if (s->buffer == STRING_MALLOC_FAIL) {
        free(s);
        return STRING_MALLOC_FAIL;
    }
    s->max_length = max_length;
    return s;
}
size_t get_string_size(safe_string *s){
    size_t size = 0;
    while (s->buffer[size] != (char) 0 && size < s->max_length){
        size++;
    }
    return size;
}

int set_string(safe_string *s, const char *str) {
    if (strlen(str) > s->max_length){
        return STRING_OVERFLOW;
    }
    for (size_t i = 0; str[i] != 0 ; i++) {
        s->buffer[i] = str[i];
    }
    return STRING_SUCCESS;
}


int append_string(safe_string *s, const char *str) {
    if (strlen(str) + get_string_size(s) > s->max_length){
        return STRING_OVERFLOW;
    }
    int count = 0;
    for (int i = get_string_size(s); i<s->max_length ; i++){
        if (str[count] == '\0'){
            break;
        }
        s->buffer[i] = str[count];
        count++;
    }
    return STRING_SUCCESS;
}


void print_string(const safe_string *str, FILE *stream) {
    if (str == NULL || str->buffer == NULL || stream == NULL) {
        return;
    }
    fputc('\"',stream);
    for (size_t i = 0; i < str->max_length; i++) {
        if (str->buffer[i] == (char) 0){continue;}
        fputc(str->buffer[i], stream);
    }
    fprintf(stream,"\"\tbuffer length : %zu\n",str->max_length);
}

safe_string *initialize_safe_string(const char * str){
    safe_string *res = create_string(strlen(str));
    set_string(res,str);
    return res;
}
void destroy_string(safe_string *s) {
    if (s != NULL) {
        free(s->buffer);
        free(s);
    }
}

