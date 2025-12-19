#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <string.h>

#define vector struct __vector_t__*
#define BASE_VECTOR_SIZE 20
#define VECTOR_INCREASER 5
#define NO_VECTOR NULL

enum vector_return_codes
{
    VECTOR_POS_CASE,
    VECTOR_VAR_ERR,
    VECTOR_MALLOC_ERR,
    VECTOR_DATA_MALLOC_ERR,
    VECTOR_REALLOC_ERR
};

struct __vector_t__
{
    void *data;
    size_t max_elems;
    size_t writen_elems;
    size_t elem_size;
};

int init_vector(vector *container, size_t elem_size);
int free_vector(vector *container);
int push_back_vector(vector container, void *elem);
int pop_back_vector(vector container);
int size_vector(vector container);

#endif
