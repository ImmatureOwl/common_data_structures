#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CUNIT_STRING_EQ(expect, actual) \
    if (strcmp(expect, actual) != 0) \
    { \
        printf("%s: expected %s but was %s [%d]", __FUNCTION__, expect, actual, __LINE__); \
        exit(-1); \
    } \

#define CUNIT_IS_NULL(actual) \
    if (actual != NULL) { \
        printf("%s: expected %s but was %p [%d]", __FUNCTION__, "NULL", actual, __LINE__); \
        exit(-1); \
    } \

#define CUNIT_TEST(name) void name()

#define CUNIT_RUNNER(...) \
int main(int argc, char *argv[]) \
{ \
    void (*tests[])() = { __VA_ARGS__ }; \
    puts("beginning tests..."); \
    int count = sizeof(tests) / sizeof(void*); \
    for(int i=0; i < count; ++i) { \
        tests[i](); \
        printf("test %d of %d passed\n", i+1, count); \
    } \
    printf("All Tests passed! [%d]", count); \
    return 0; \
} \
