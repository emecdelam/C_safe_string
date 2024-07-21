# Safer string

This repo contains the basis for safer string in C, instead of using a null terminated char predefined buffer are used. This avoid overflow as anything outside the buffer won't be written.

When creating a buffer, every char inside is set at 0 and a datastructure stores the maximum length of the buffer.

For now I will stick with that I might update the structure to also keep the place of the last char. Currently the length can be get with the function `get_string_size` that checks for every 0 char inside the buffer.

The only unsafe operation is while converting from an unsafe string to a safe string as strlen is used there

## testing

There are some tests made possible by [tunit](https://github.com/tdaron/tunit) big thanks to the creator

## docs

The safe string data structure is defined in the header as :
```c
typedef struct {
    char *buffer;
    size_t max_length;
} safe_string;
```
```cvoid *custom_calloc(size_t size)``` is a function not meant for user usage, I use it because it allows me to return `STRING_MALLOC_FAIL` for strings of length 0

```csafe_string *create_string(size_t max_length)``` allocates memory for the structure and returns a pointer or `STRING_MALLOC_FAIL`

```csize_t get_string_size(safe_string *s)``` returns the number of char until it finds a 0 or the end of the buffer

```cint set_string(safe_string *s, const char *str)``` returns `STRING_OVERFLOW` if the `str` is too big for the buffer or `STRING_SUCCESS`

```cint append_string(safe_string *s, const char *str)``` returns `STRING_OVERFLOW` if the `str` and the data already inside s is too big for the buffer or `STRING_SUCCESS`, it is to note that it uses `get_string_size` to know where to append

```cvoid print_string(const safe_string *str, FILE *stream)``` prints the string to the stream under the following format : `"{}"\tbuffer length : {}`

```csafe_string *initialize_safe_string(const char * str)``` easily creates safe string ignoring `malloc` possible fails, the goto option if you are sure that `malloc` won't fail, it also uses `strlen` to determine the size of the buffer to allocate,
```c
initialize_safe_string("Hello");
```
will allocate a buffer of size 5

```cvoid destroy_string(safe_string *s)``` completely frees a `safe_string`