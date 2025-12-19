#include "vector.h"

int init_vector(vector *container, size_t elem_size)
{
    int rc = (container == NULL || elem_size == 0) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE)
    {
        *container = malloc(sizeof(struct __vector_t__));
        if (*container == NULL)
            rc = VECTOR_MALLOC_ERR;
    }
    if (rc == VECTOR_POS_CASE)
    {
        (*container)->data = malloc(elem_size * BASE_VECTOR_SIZE);
        if ((*container)->data == NULL)
            rc = VECTOR_DATA_MALLOC_ERR;
        else
        {
            (*container)->max_elems = BASE_VECTOR_SIZE;
            (*container)->elem_size = elem_size;
            (*container)->writen_elems = 0;
        }
    }
    return rc;
}

int free_vector(vector *container)
{
    int rc = (container == NULL) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE)
    {
        free((*container)->data);
        free(*container);
        *container = NO_VECTOR;
    }
    return rc;
}

int push_back_vector(vector container, void *elem)
{
    int rc = (container == NO_VECTOR || elem == NULL) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE && container->max_elems == container->writen_elems)
    {
        void *help_ptr = realloc(container->data, (container->max_elems += VECTOR_INCREASER + 1) * container->elem_size);
        if (help_ptr == NULL)
            rc = VECTOR_REALLOC_ERR;
        else
            container->data = help_ptr;
    }
    if (rc == VECTOR_POS_CASE)
        memcpy((void*)((char*)container->data + container->elem_size * (container->writen_elems)++), elem, container->elem_size);
    return rc;
}

int pop_back_vector(vector container)
{
    int rc = (container == NO_VECTOR) ? VECTOR_VAR_ERR : VECTOR_POS_CASE;
    if (rc == VECTOR_POS_CASE && container->writen_elems != 0)
    {
        (container->writen_elems)--;
        if (container->max_elems - container->writen_elems > VECTOR_INCREASER)
        {
            void *help_ptr = realloc(container->data, (container->max_elems -= VECTOR_INCREASER + 1) * container->elem_size);
            if (help_ptr == NULL)
                rc = VECTOR_REALLOC_ERR;
            else
                container->data = help_ptr;
        }
    }
    return rc;
}

int size_vector(vector container)
{
    return (container == NO_VECTOR) ? 0 : container->writen_elems;
}
