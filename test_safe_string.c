#include <assert.h>
#include <stdio.h>
#define TUNIT_IMPLEMENTATION
#include "tunit.h"
#include "safe_string.c"

void test_custom_calloc_fail()
{
    t_assert_int64((long int) STRING_MALLOC_FAIL, == , (long int)custom_calloc(0));

}
void test_custom_calloc_buf()
{
    t_assert_int(0, == , ((char* )custom_calloc(2))[0])
    t_assert_int(0, == , ((char* )custom_calloc(2))[1])
}
void test_create_string_fail()
{
    safe_string *str = create_string(0);
    t_assert_int64((long int) STRING_MALLOC_FAIL, == ,(long int)str);
}
void test_create_string_128()
{
    safe_string *str = create_string(128);
    t_assert_int(0,==,str->buffer[0]);
    t_assert_int(0,==,str->buffer[127]);
    t_assert_int(128,==,(int) str->max_length);
    destroy_string(str);
}
void test_get_string_size()
{
    safe_string *str = create_string(32);
    t_assert_int(0, == , (int) get_string_size(str));
    str->buffer[0] = 'H';
    str->buffer[1] = 'e';
    str->buffer[2] = 'l';
    str->buffer[3] = 'l';
    str->buffer[4] = 'o';
    t_assert_int(5, == , (int) get_string_size(str));
    destroy_string(str);
}
void test_set_string_fail()
{
    safe_string *str = create_string(8);
    t_assert_int(STRING_OVERFLOW, == ,set_string(str, "Hello world!"));
    destroy_string(str);
}
void test_set_string(){
    safe_string *str = create_string(8);
    t_assert_int(STRING_SUCCESS, == , set_string(str, "Hello"));
    t_assert_char(str->buffer[0], == ,'H');
    t_assert_char(str->buffer[1], == , 'e');
    t_assert_char(str->buffer[2], == , 'l');
    t_assert_char(str->buffer[3], == , 'l');
    t_assert_char(str->buffer[4], == , 'o');
    t_assert_char(str->buffer[5], == , (char) 0 );
    t_assert_char(str->buffer[6], == , (char) 0 );
    t_assert_char(str->buffer[7], == , (char) 0 );
    destroy_string(str);
}
void test_append_string_fail(){
    safe_string *str = create_string(8);
    set_string(str, "Hello");
    t_assert_int(STRING_OVERFLOW, == , append_string(str," World"));
}
void test_append_string(){
    safe_string *str = create_string(16);
    set_string(str,"Hello");
    t_assert_int(STRING_SUCCESS, == ,append_string(str," World !"));
    t_assert_char(str->buffer[0], == ,'H');
    t_assert_char(str->buffer[4], == , 'o');
    t_assert_char(str->buffer[5], == , ' ');
    t_assert_char(str->buffer[6], == , 'W');
    t_assert_char(str->buffer[12], == , '!' );
    t_assert_char(str->buffer[13], == , (char) 0 );
    t_assert_char(str->buffer[14], == , (char) 0 );
    t_assert_char(str->buffer[15], == , (char) 0 );
}


int main(int argc, char** argv)
{
    testsuite_t *s_custom_calloc = t_registerTestSuite("Custom Calloc");
    t_addTestToSuite(s_custom_calloc, "Calloc fail",test_custom_calloc_fail);
    t_addTestToSuite(s_custom_calloc, "Calloc buffer initialisation",test_custom_calloc_buf);

    testsuite_t *s_create_string = t_registerTestSuite("Initiate safe String");
    t_addTestToSuite(s_create_string,"Create string fail",test_create_string_fail);
    t_addTestToSuite(s_create_string,"Create 128 bits string",test_create_string_128);

    testsuite_t *s_get_string_size = t_registerTestSuite("Get string size");
    t_addTestToSuite(s_get_string_size, "Get string size", test_get_string_size);

    testsuite_t *s_set_string = t_registerTestSuite("Set string");
    t_addTestToSuite(s_set_string, "Add too long string to safe string", test_set_string_fail);
    t_addTestToSuite(s_set_string, "Add unsafe string to safe string", test_set_string);

    testsuite_t *s_append_string = t_registerTestSuite("Append string");
    t_addTestToSuite(s_append_string,"Append overflow",test_append_string_fail);
    t_addTestToSuite(s_append_string,"Append string to string",test_append_string);

    return t_runSuites(argc, argv);
}