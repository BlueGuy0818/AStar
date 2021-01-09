#ifndef _UTF8VECTOR
#define _UTF8VECTOR

#include <stddef.h>
#include <string>

using namespace std;

typedef struct _utf8vector *utf8vector;

struct _utf8vector 
{
	const char *utf8_str;
	unsigned int length;
	unsigned int index;
};

utf8vector utf8vector_create(const char *utf8, int string_length);
void utf8vector_reset(utf8vector vector);
wchar_t utf8vector_next_unichar_with_raw(utf8vector vector, string& utf8, const char **raw, int *raw_length);
wchar_t utf8vector_next_unichar(utf8vector vector, string& utf8);
int utf8vector_uni_count(utf8vector vector, string& utf8);
void utf8vector_free(utf8vector vector);
#endif